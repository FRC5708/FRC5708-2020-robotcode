#include "commands/Autonomous.h"
#include "commands/DriveToPoint.h"
#include "subsystems/Odometry.h"
#include "commands/TurnToAngle.h"
#include "Robot.h"
#include <frc2/command/ParallelRaceGroup.h>


using namespace units;

AutonomousCommand::AutonomousCommand() {
	
	startSelect.SetDefaultOption("Center", 'C');
	startSelect.AddOption("Left", 'L');
	startSelect.AddOption("Right", 'R');
	
	whetherToTrenchRun.SetDefaultOption("Yes", true);
	whetherToTrenchRun.AddOption("No", false);
	
}


class ContinuousIntakeCommand : public frc2::CommandHelper<frc2::CommandBase, ContinuousIntakeCommand> {
public:
	ContinuousIntakeCommand() {
		AddRequirements(&Robot::GetRobot()->intake);
	}
protected:
	void Execute() override {
		Robot::GetRobot()->intake.setIntake(Intake::intake_mode::intake);
	}
	void End(bool interrupted) override {
		Robot::GetRobot()->intake.setIntake(Intake::intake_mode::off);
	}
};



// For positions: pefer to game manual and https://firstfrc.blob.core.windows.net/frc2020/PlayingField/LayoutandMarkingDiagram.pdf
void AutonomousCommand::Initialize() {
	
	// Set starting position
	// Y is SIDEWAYS, X is FORWARDS
	// Left is positive Y, forwards is positive X
	// 0,0 is at the back center of the opponent's SECTOR (behind the starting point)
	
	inch_t yStart((52*12 + 5 + 1.0/4.0) / 2.0 - 4*12 + 7 + 1.0/2.0); // Aligned with outside of trench run
	inch_t xStart(10*12); // Centered on initiation line
	frc::Translation2d start;
	
	switch (startSelect.GetSelected()) {
		case 'R': start = { xStart, -yStart }; break;
		case 'L': start = { xStart, yStart }; break;
		default: 
		std::cout << "Bad locationSelect" << std::endl;
		[[fallthrough]]; // Suppresses the "implicit fallthrough" warning
		case 'C': start = { xStart, inch_t(0) }; break;
	}
	
	Robot::GetRobot()->odometry.Reset(frc::Pose2d(start, frc::Rotation2d(degree_t(0))));
	
	// Turn towards shooter with precise angle
	frc::Translation2d targetPos{inch_t(0), -inch_t((52*12 + 5 + 1.0/4.0) / 2.0 - 94.66)};
	AddCommands(TurnToPoint(targetPos));
	
	// TODO: Shoot	
	
	if (whetherToTrenchRun.GetSelected()) {
		frc::Translation2d trench1 = start + frc::Translation2d{inch_t(40), inch_t(0)};
		AddCommands(DriveToPoint(trench1));
		frc::Translation2d trench2{ inch_t(138), inch_t(190) };
		AddCommands(DriveToPoint(trench2, true));
		
		// Charge the trench run
		frc::Translation2d trenchEnd{inch_t(430), trench2.Y()};
		// We turn while stationary as there's not enough clearance to make a wide turn by the trench run
		// Activate intake while in trench
		AddCommands(frc2::ParallelRaceGroup(
			ContinuousIntakeCommand(), 
			SequentialCommandGroup(TurnToPoint(trenchEnd), DriveToPoint(trenchEnd)
		)));
	}
	else {
		// Exit initiation line
		AddCommands(DriveToPoint(start + frc::Translation2d{inch_t(30), inch_t(0)}));
	}
}