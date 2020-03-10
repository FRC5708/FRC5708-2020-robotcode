#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
#include "DebugValues.h"
#include "subsystems/Drivetrain.h"
#include <units/units.h>

class Odometry : public frc2::SubsystemBase {
    frc2::Command* currentOwner;
    void Periodic() override;
    //creating odometry object
    frc::DifferentialDriveOdometry m_odometry;
    Drivetrain* drivetrain;

    bool leftEncoderGood = false, rightEncoderGood = false;
    void checkEncoders();
public:
    Odometry();
    static Odometry* getOdometry();
    frc::Pose2d currentPos;
    units::length::meter_t getRobotx();
    units::length::meter_t getRoboty();
    units::angle::degree_t getRobotdeg();
    
    // Returns counterclockwise-positive, which is the convention everywhere else in the code.
    inline double GetGyroAngle() { return -gyro->GetAngle(); };

    frc::Gyro* const gyro;
	frc::Encoder* const leftEncoder;
	frc::Encoder* const rightEncoder;

    std::pair<units::meter_t, units::meter_t> GetEncoderDistances();

    void Reset(frc::Pose2d newPose); //TODO: this function should only be able to be called if one command has exclusive control over the odometry, as it will screw everything up, otherwise. Command groups?

private:
};

//mpose output angle output x y