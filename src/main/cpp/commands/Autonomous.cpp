  #include "commands/Autonomous.h"
#include "commands/DriveToPoint.h"
#include "commands/TurnToAngle.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/ParallelRaceGroup.h>
#include <frc2/command/WaitCommand.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Odometry.h"
#include "subsystems/Intake.h"
#include "subsystems/Shooter.h"


using namespace units;

AutonomousCommand::AutonomousCommand() {
	
	startSelect.SetDefaultOption("Center", 'C');
	startSelect.AddOption("Left", 'L');
	startSelect.AddOption("Right", 'R');
	frc::SmartDashboard::PutData("Starting Pos", &startSelect);
	
	whetherToTrenchRun.SetDefaultOption("Yes", true);
	whetherToTrenchRun.AddOption("No", false);
	
	frc::SmartDashboard::PutData("Trench Run?", &whetherToTrenchRun);
}


class ContinuousIntakeCommand : public frc2::CommandHelper<frc2::CommandBase, ContinuousIntakeCommand> {
protected:
	Intake* intake;
	void Execute() override {
		intake->setIntake(Intake::intake_mode::intake);
	}
	void End(bool interrupted) override {
		intake->setIntake(Intake::intake_mode::off);
	}
public:
	ContinuousIntakeCommand() : intake(Intake::getIntake()){
		AddRequirements(intake);
	}
};

class ContinuousShooterCommand : public frc2::CommandHelper<frc2::CommandBase, ContinuousShooterCommand> { 
protected:
	Shooter* shooter;
	void Execute() override {
		shooter->setShooterWheels(Shooter::defaultSpeed);
	}
	void End(bool interrupted) override {
		shooter->setShooterWheels(0);
	}
public:
	ContinuousShooterCommand() : shooter(Shooter::getShooter()){
		AddRequirements(shooter);
	}
};
class ContinuousDriveCommand : public frc2::CommandHelper<frc2::CommandBase, ContinuousShooterCommand> { 
protected:
	double power;
	Drivetrain* drivetrain;
	void Execute() override {
		drivetrain->Drive(power, power);
	}
	void End(bool interrupted) override {
		drivetrain->Drive(0, 0);
	}
public:
	ContinuousDriveCommand(double power) : power(power),drivetrain(Drivetrain::getDrivetrain()){
		AddRequirements(drivetrain);
	}
};



// For positions: pefer to game manual and https://firstfrc.blob.core.windows.net/frc2020/PlayingField/LayoutandMarkingDiagram.pdf
void AutonomousCommand::SetupAuton() {
	
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
	
	Odometry::getOdometry()->Reset(frc::Pose2d(start, frc::Rotation2d(degree_t(0))));
	
	// Turn towards shooter with precise angle
	frc::Translation2d targetPos{inch_t(0), -inch_t((52*12 + 5 + 1.0/4.0) / 2.0 - 94.66)};
	AddCommands(TurnToPoint(targetPos));
	// TODO: correct timing
	AddCommands(frc2::WaitCommand(second_t(0.5)), 
	frc2::ParallelRaceGroup(frc2::WaitCommand(second_t(5.0)), ContinuousShooterCommand()));
	
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
		//frc::Translation2d endPoint = start + frc::Translation2d{inch_t(30), inch_t(0)};
		//AddCommands(TurnToPoint(endPoint, true), DriveToPoint(endPoint, true, true));
		
		// Stop-gap timing based auton: halt after one second
		AddCommands(TurnToAngle(degree_t(0)), 
		frc2::ParallelRaceGroup(frc2::WaitCommand(second_t(1)), ContinuousDriveCommand(-0.4)));
	}
}