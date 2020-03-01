#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include "DebugValues.h"

class Odometry : public frc2::SubsystemBase {
    void Periodic() override;
    //creating odometry object
    frc::DifferentialDriveOdometry m_odometry;
public:
    Odometry();
    static Odometry* getOdometry();
    frc::Pose2d currentPos;
    units::length::meter_t getRobotx();
    units::length::meter_t getRoboty();
    units::angle::degree_t getRobotdeg();
    
    void Reset(frc::Pose2d newPose); //TODO: this function should only be able to be called if one command has exclusive control over the odometry, as it will screw everything up, otherwise. Command groups?

private:
};

//mpose output angle output x y