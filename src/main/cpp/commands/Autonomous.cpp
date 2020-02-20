#include "commands/Autonomous.h"
#include "commands/DriveToPoint.h"
#include "subsystems/Odometry.h"
#include "commands/TurnToAngle.h"
#include "Robot.h"


using namespace units;

AutonomousCommand::AutonomousCommand() {
	
	startSelect.SetDefaultOption("Center", 'C');
	startSelect.AddOption("Left", 'L');
	startSelect.AddOption("Right", 'R');
	
	whetherToTrenchRun.SetDefaultOption("Yes", true);
	whetherToTrenchRun.AddOption("No", false);
	
}

// For positions: pefer to game manual and https://firstfrc.blob.core.windows.net/frc2020/PlayingField/LayoutandMarkingDiagram.pdf
void AutonomousCommand::Initialize() {
	
	// Set starting position
	
	inch_t xStart((52*12 + 5 + 1.0/4.0) / 2.0 - 4*12 + 7 + 1.0/2.0); // Aligned with outside of trench run
	inch_t yStart(10*12); // Centered on initiation line
	frc::Translation2d start;
	
	switch (startSelect.GetSelected()) {
		case 'R': start = { xStart, yStart }; break;
		case 'L': start = { -xStart, yStart }; break;
		default: 
		std::cout << "Bad locationSelect" << std::endl;
		case 'C': start = { inch_t(0), yStart }; break;
	}
	
	// Turn towards shooter with precise angle
	frc::Translation2d targetPos{inch_t((52*12 + 5 + 1.0/4.0) / 2.0 - 94.66), inch_t(0)};
	AddCommands(TurnToAngle(
		&Robot::GetRobot()->drivetrain, 
		degree_t(360) - units::math::atan2(targetPos.X() - start.X(), targetPos.Y() - start.Y())
	));
	
	// TODO: Shoot	
	
	if (whetherToTrenchRun.GetSelected()) {
		frc::Translation2d trench1 = start + frc::Translation2d{inch_t(0), inch_t(40)};
		frc::Translation2d trench2{inch_t(138), inch_t(190)};
		
		// TODO: activate intake
		// Charge the trench run
		frc::Translation2d trenchEnd{trench2.X(), inch_t(430)};
	}
	else {
		// Exit initiation line
		frc::Translation2d exiter = start + frc::Translation2d{inch_t(0), inch_t(30)};
	}
}