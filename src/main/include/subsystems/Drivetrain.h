#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/Encoder.h"
#include <vector>
#include <frc/Victor.h>

#include "DIOMaps.h"

class Drivetrain : protected frc2::SubsystemBase {
	private:
	frc::Encoder* const leftEncoder = new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1]);
	frc::Encoder* const rightEncoder = new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1]);
	frc::SpeedController* const FLMotor = new frc::Victor(frontLeftMotorChannel);
	frc::SpeedController* const FRMotor = new frc::Victor(frontRightMotorChannel);
	frc::SpeedController* const BLMotor = new frc::Victor(backLeftMotorChannel);
	frc::SpeedController* const BRMotor = new frc::Victor(backRightMotorChannel);
	public:
	Drivetrain();
	void Drive(double left, double right);
	void DrivePolar(double power, double turn);
	double boundValue(double value, double bound);
	std::vector<double> getMotorPowers();
};