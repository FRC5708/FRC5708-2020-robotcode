#pragma once

#include <frc2/command/SubsystemBase.h>
#include <vector>
#include <frc/SpeedController.h>
#include <frc/Encoder.h>
#include <frc/GyroBase.h>
#include <units/units.h>
#include "DebugValues.h"
#include <frc2/command/CommandBase.h>

class Drivetrain : public frc2::SubsystemBase {
protected:
	frc2::Command* currentOwner;
	const static bool usingTalons=false;
	frc::SpeedController* FLMotor;
	frc::SpeedController* FRMotor;	
	frc::SpeedController* BLMotor;
	frc::SpeedController* BRMotor;
	
	void Periodic() override;
public:
	Drivetrain();
	static Drivetrain* getDrivetrain();
	void Drive(double left, double right);
	void DrivePolar(double power, double turn);
	double boundValue(double value, double bound);
	
	std::vector<double> getMotorPowers();
	
};