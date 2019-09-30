#pragma once

#include "frc/commands/Subsystem.h"
#include "frc/Spark.h"
#include "frc/Encoder.h"

#include "DIOMaps.h"

class Drivetrain : protected frc::Subsystem {
    private:
    frc::Encoder* const leftEncoder = new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1]);
    frc::Encoder* const rightEncoder = new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1]);
    frc::SpeedController* const FLMotor = new frc::Spark(frontLeftMotorChannel);
    frc::SpeedController* const FRMotor = new frc::Spark(frontRightMotorChannel);
    frc::SpeedController* const BLMotor = new frc::Spark(backLeftMotorChannel);
    frc::SpeedController* const BRMotor = new frc::Spark(backRightMotorChannel);
    public:
    Drivetrain();
    void Drive(double left, double right);
    void DrivePolar(double power, double turn);
};