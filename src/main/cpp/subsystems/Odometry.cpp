
#include <iostream>

#include "subsystems/Drivetrain.h"
#include "subsystems/Odometry.h"
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include "Robot.h"

Odometry::Odometry() : m_odometry{frc::Rotation2d {units::degree_t(Robot::GetRobot()->drivetrain.GetGyroAngle())},
    frc::Pose2d{units::meter_t(0),units::meter_t(0), frc::Rotation2d {units::degree_t(0)}}} {
    
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

    currentPos = m_odometry.Update(gyroAngle,
         units::meter_t(Robot::GetRobot()->drivetrain.leftEncoder->GetDistance()),
         units::meter_t(Robot::GetRobot()->drivetrain.rightEncoder->GetDistance())
    );
    std::cout << "X: " << currentPos.Translation().X() << ", Y: " << currentPos.Translation().Y() << ", ROT: " << currentPos.Rotation().Degrees() << std::endl;
}