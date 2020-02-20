#include <frc2/command/CommandBase.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc2/command/CommandHelper.h>
#include <frc/smartdashboard/SendableChooser.h>


class AutonomousCommand : public frc2::CommandHelper<frc2::SequentialCommandGroup, AutonomousCommand> {
	
	AutonomousCommand();
	
	void Initialize() override;
	
	frc::SendableChooser<char> startSelect;
	frc::SendableChooser<bool> whetherToTrenchRun;
};



class Autonomous {
	
	Autonomous();
	
};