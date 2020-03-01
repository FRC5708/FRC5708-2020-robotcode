#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>

constexpr bool const DEBUG_ODOMETRY=false;

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
    
    void Reset(frc::Pose2d newPose);

private:
};

//mpose output angle output x y