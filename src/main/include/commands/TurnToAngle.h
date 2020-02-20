#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/PIDCommand.h>

#include "subsystems/VisionReceiver.h"
#include <units/units.h>

class Drivetrain;

class TurnToAngle : public frc2::PIDCommand {
protected:
	Drivetrain* drivetrain;
public:
	TurnToAngle(Drivetrain* drivetrain, units::degree_t targetRotation);
	units::degree_t targetRotation;
	
	 bool IsFinished() override;
	
	// When copying, must change lambdas so that they refer to the correct this
	TurnToAngle(TurnToAngle& otherMe);
};

class VisionDrive : public TurnToAngle {
private:
	VisionReceiver::PossibleTarget currentTarget;
	void SetAngle();
public:

	struct Point {
		double x, y;
	};

	units::degree_t targetRotation;

	VisionDrive();
	void Initialize() override;
	void Execute() override;
	void End(bool interrupted) override;
};