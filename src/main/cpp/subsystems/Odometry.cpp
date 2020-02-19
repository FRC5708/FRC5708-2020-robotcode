
#include <iostream>

#include "subsystems/Drivetrain.h"
#include "subsystems/Odometry.h"
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include "Robot.h"


void Odometry::Periodic() {
    frc::Rotation2d gyroAngle{units::degree_t(gyro->GetAngle())};

    currentPos = m_odometry.Update(gyroAngle,
         units::meter_t(Robot::GetRobot()->drivetrain.leftEncoder->GetDistance()),
         units::meter_t(Robot::GetRobot()->drivetrain.rightEncoder->GetDistance())
    );
    std::cout << "X: " << currentPos.Translation().X() << ", Y: " << currentPos.Translation().Y() << ", ROT: " << currentPos.Rotation().Degrees() << std::endl;
}