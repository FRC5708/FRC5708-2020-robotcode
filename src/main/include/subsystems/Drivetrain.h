#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>

#include "DIOMaps.h"

class Drivetrain : protected frc2::SubsystemBase {
	private:
	frc::Encoder* const leftEncoder = new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1]);
	frc::Encoder* const rightEncoder = new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1]);
	frc::SpeedController* FLMotor;
	frc::SpeedController* FRMotor;
	frc::SpeedController* BLMotor;
	frc::SpeedController* BRMotor;
	bool usingTalons = false;
	public:
	Drivetrain();
	void Drive(double left, double right);
	void DrivePolar(double power, double turn);
	double boundValue(double value, double bound);
};