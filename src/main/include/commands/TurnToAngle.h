#pragma once

#include <iostream>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/PIDCommand.h>
#include <frc/geometry/Translation2d.h>
#include <units/units.h>
#include "commands/DriveWithJoystick.h"
#include "subsystems/VisionReceiver.h"

class Drivetrain;

class TurnToAngle : public frc2::PIDCommand {
public:
	TurnToAngle(units::degree_t targetRotation);
	units::degree_t targetRotation;
	
	bool IsFinished() override;
	void End(bool interrupted) override;
	
	// When copying, must change lambdas so that they refer to the correct this
	TurnToAngle(const TurnToAngle& otherMe);
};

class TurnToPoint : public TurnToAngle {
public:
	frc::Translation2d targetPoint;
	bool backwards;
	TurnToPoint(frc::Translation2d point, bool backwards = false);
protected:
	void Initialize() override;
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