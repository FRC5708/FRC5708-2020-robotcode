#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/CommandHelper.h>
#include <frc/smartdashboard/SendableChooser.h>


// It turns out that CommandHelper adds problems and isn't really necessary... Just don't use WithTimeout(), BeforeStarting(), and friends.
class AutonomousCommand : public frc2::SequentialCommandGroup {
public:
	AutonomousCommand();
	
	void SetupAuton();
	
private:
	frc::SendableChooser<char> startSelect;
	frc::SendableChooser<bool> whetherToTrenchRun;
};

