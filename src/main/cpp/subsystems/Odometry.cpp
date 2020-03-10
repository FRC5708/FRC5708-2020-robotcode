#include "subsystems/Odometry.h"
#include <iostream>
#include <frc/ADXRS450_Gyro.h>
#include "DIOMaps.h"

#include <frc/kinematics/DifferentialDriveOdometry.h>
#include "subsystems/Drivetrain.h"

using namespace units;

constexpr inch_t ROBOT_WIDTH(28);
constexpr inch_t ROBOT_LENGTH(28.25);

Odometry odometryInstance;

Odometry::Odometry() : 
    m_odometry{frc::Rotation2d {units::degree_t(0)}, frc::Pose2d{units::meter_t(0),units::meter_t(0), frc::Rotation2d {units::degree_t(0)}}}, 
    drivetrain(Drivetrain::getDrivetrain()),
    gyro(new frc::ADXRS450_Gyro()),
    leftEncoder(new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1], false)),
    rightEncoder(new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1], true)) {
    
    constexpr double metersPerPulse = units::meter_t(units::inch_t(6.0)).value() * M_PI / 360.0;
	leftEncoder->SetDistancePerPulse(metersPerPulse);
	rightEncoder->SetDistancePerPulse(metersPerPulse);
    
    assert(this == &odometryInstance); // there should only be one instance.
    if(DEBUG_CONSTRUCTORS) std::cout << "Odometry initialized." << std::endl;
}
Odometry* Odometry::getOdometry(){
	return &odometryInstance;
}
/*
*returns the Pose2d x as a meter_t
*/
units::length::meter_t Odometry::getRobotx() {
    return currentPos.Translation().X();
}
/*
*returns the Pose2d y as a meter_t
*/
units::length::meter_t Odometry::getRoboty() {
    return currentPos.Translation().Y();
}
/*
*returns the Pose2d degrees as a degree_t
*/
units::angle::degree_t Odometry::getRobotdeg() {
    return currentPos.Rotation().Degrees();
}


void Odometry::Periodic() {
    frc::Rotation2d gyroAngle{units::degree_t(GetGyroAngle())};
    auto encoders = GetEncoderDistances();
    

    currentPos = m_odometry.Update(gyroAngle, encoders.first, encoders.second);
    static int ticks = 0;
    ++ticks;
    if (DEBUG_ODOMETRY && ticks % 50 == 0) std::cout << "X: " << currentPos.Translation().X() << ", Y: " << currentPos.Translation().Y() << ", ROT: " << currentPos.Rotation().Degrees() << std::endl;
    if(DEBUG_REQUIREMENTS && GetCurrentCommand()!=currentOwner){
		currentOwner=GetCurrentCommand();
		std::cout << "Ownership of Odometry switched to " << currentOwner->GetName() << std::endl;
	}
}

void Odometry::Reset(frc::Pose2d newPose) {
    
    leftEncoder->Reset();
    rightEncoder->Reset();
    // Note: This IS necessary, despite DifferentialDriveOdometry saying it isn't, because of the way TurnToPoint is implemented 
    gyro->Reset();
    
    m_odometry.ResetPosition(newPose, frc::Rotation2d {units::degree_t(GetGyroAngle())});
}

void Odometry::checkEncoders() {
	if (!leftEncoderGood) leftEncoderGood = fabs(leftEncoder->GetDistance()) > 0.1;
	if (!rightEncoderGood) rightEncoderGood = fabs(rightEncoder->GetDistance()) > 0.1;
}
std::pair<units::meter_t, units::meter_t> Odometry::GetEncoderDistances() {
	checkEncoders();
	meter_t leftDistance(leftEncoder->GetDistance());
	meter_t rightDistance(rightEncoder->GetDistance());
	
	if (!leftEncoderGood && rightEncoderGood) {
		// emulate with gyro
		return { rightDistance - radian_t(degree_t(GetGyroAngle())).value() * ROBOT_WIDTH, rightDistance };
	}
	else if (!rightEncoderGood && leftEncoderGood) {
		return { leftDistance, leftDistance + radian_t(degree_t(GetGyroAngle())).value() * ROBOT_WIDTH };
	}
	else {
		// both encoders, yay!
		// or maybe no encoders
		return {leftDistance, rightDistance};
	}
}