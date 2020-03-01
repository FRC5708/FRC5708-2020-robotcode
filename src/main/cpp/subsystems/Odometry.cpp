#include "subsystems/Odometry.h"

#include <iostream>

#include "subsystems/Drivetrain.h"
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include "Robot.h"

Odometry* odometryInstance=nullptr;

Odometry::Odometry() : m_odometry{frc::Rotation2d {units::degree_t(0)},
    frc::Pose2d{units::meter_t(0),units::meter_t(0), frc::Rotation2d {units::degree_t(0)}}} {
    
    assert(odometryInstance==nullptr); //We should only have one shooter.
	odometryInstance=this;
}
Odometry* Odometry::getOdometry(){
	assert(odometryInstance!=nullptr);
	return odometryInstance;
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
    frc::Rotation2d gyroAngle{units::degree_t(Robot::GetRobot()->drivetrain.GetGyroAngle())};
    auto encoders = Robot::GetRobot()->drivetrain.GetEncoderDistances();
    

    currentPos = m_odometry.Update(gyroAngle, encoders.first, encoders.second);
    static int ticks = 0;
    ++ticks;
    if (DEBUG_ODOMETRY && ticks % 50 == 0) std::cout << "X: " << currentPos.Translation().X() << ", Y: " << currentPos.Translation().Y() << ", ROT: " << currentPos.Rotation().Degrees() << std::endl;
}

void Odometry::Reset(frc::Pose2d newPose) {
    
    Robot::GetRobot()->drivetrain.leftEncoder->Reset();
    Robot::GetRobot()->drivetrain.rightEncoder->Reset();
    // Note: This IS necessary, despite DifferentialDriveOdometry saying it isn't, because of the way TurnToPoint is implemented 
    Robot::GetRobot()->drivetrain.gyro->Reset();
    
    m_odometry.ResetPosition(newPose, frc::Rotation2d {units::degree_t(Robot::GetRobot()->drivetrain.GetGyroAngle())});
}