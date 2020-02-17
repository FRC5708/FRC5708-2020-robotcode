#pragma once

#include <frc/ADXRS450_Gyro.h>
#include <frc2/command/SubsystemBase.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include "subsystems/Odometry.h"



class Odometry : public frc2::SubsystemBase {
    void Periodic() override;
    //creating odometry object
    frc::DifferentialDriveOdometry m_odometry{frc::Rotation2d {units::degree_t(gyro->GetAngle())},
    frc::Pose2d{units::meter_t(0),units::meter_t(0), frc::Rotation2d {units::degree_t(0)}}};
    frc::Gyro* const gyro = new frc::ADXRS450_Gyro();
    //frc::DifferentialDriveOdometry CurrentPos; trying to create a variable with the pose 2d type

private:
};

//mpose output angle output x y