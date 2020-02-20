#pragma once

#include <frc2/command/SubsystemBase.h>
#include "frc/Encoder.h"
#include <vector>
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>
#include <frc/ADXRS450_Gyro.h>

#include "DIOMaps.h"

class Drivetrain : protected frc2::SubsystemBase {
	private:
	const static bool usingTalons=false;
	frc::SpeedController* FLMotor;
	frc::SpeedController* FRMotor;	
	frc::SpeedController* BLMotor;
	frc::SpeedController* BRMotor;
	public:
	Drivetrain();
	void Drive(double left, double right);
	void DrivePolar(double power, double turn);
	double boundValue(double value, double bound);
	
    frc::Gyro* const gyro = new frc::ADXRS450_Gyro();
	frc::Encoder* const leftEncoder = new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1]);
	frc::Encoder* const rightEncoder = new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1]);
	std::vector<double> getMotorPowers();
};