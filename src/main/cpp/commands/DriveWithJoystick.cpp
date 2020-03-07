#include "commands/DriveWithJoystick.h"
#include <iostream>
#include <frc2/command/CommandHelper.h>
#include "Robot.h"

// buttons on xbox:
// 1=A, 2=B, 3=X, 4=Y, 5=left bumper, 6=right bumper, 7=Back, 8=Start, 9=left joystick, 10=right joystick


// constexpr int INTAKE_BUTTON = 5, 🤖 = 6;

namespace DriveWithJoystick {

double inputTransform(double input, double minPowerOutput, double inputDeadZone, 
		 double inputChangePosition = 0.75, double outputChangePosition = 0.5) {

	double output = 0;
	double correctedInput = (fabs(input) - inputDeadZone) / (1 - inputDeadZone);
	
	if (correctedInput <= 0) {
		return 0;
	}
	else if (correctedInput <= inputChangePosition) {
		output = (correctedInput / inputChangePosition * (outputChangePosition - minPowerOutput)) + minPowerOutput;
	}
	else {
		output = (correctedInput - inputChangePosition)
				/ (1 - inputChangePosition)
				* (1 - outputChangePosition)
				+ outputChangePosition;
	}
	if (input < 0) output = -output;
	return output;
}

void powerRampup(double input, double* outputVar) {
	if ((fabs(input) < fabs(*outputVar)) && ((input < 0 && *outputVar < 0 ) || (input > 0 && *outputVar > 0))){
		*outputVar = input;
		return;
	} 
	int sign = (input > 0) ? 1 : -1;
	*outputVar += 0.1*sign;
	
}

DoDrivetrain::DoDrivetrain(Drivetrain* drivetrain) : drivetrain(drivetrain),controller(&Robot::GetRobot()->controller){
   AddRequirements({drivetrain});
}
void DoDrivetrain::Initialize() {
	controller = &Robot::GetRobot()->controller;
}
void DoDrivetrain::Execute() {
	//Default POV is Shooter.
	double turn = 0;
	double power = 0;

	turn = -controller->GetX(frc::GenericHID::JoystickHand::kLeftHand);
	power = controller->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand)-controller->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand);
	
	turn = inputTransform(turn, 0, 0.1);
	power = inputTransform(power, 0.15, 0.03);
	
	if(controller->GetYButton()){ //If we're in creep mode
		turn *= creepRate;
		power *= creepRate;
	}
	if(Robot::GetRobot()->POV==robotPOV::IntakePOV){
		power = -power; //Switch forwards and backwards.
	}
	power *= .7; //Intentionally limit ourselves.

	//std::cout << "doDrivetrain executing" << std::endl;
	drivetrain->DrivePolar(power, turn);
}
void DoDrivetrain::End(bool interrupted) {
	std::cout << "doDrivetrain ending" << std::endl;
	drivetrain->Drive(0, 0);
}

DoShooter::DoShooter(Shooter* shooter) : shooter(shooter),controller(&Robot::GetRobot()->controller){
   AddRequirements({shooter});
}
void DoShooter::Initialize() {
	controller = &Robot::GetRobot()->controller;
}
void DoShooter::Execute() {

	// Controls shooting wheels
	if (controller->GetXButtonPressed()) {
		isRunning = !isRunning; //Toggle shooter state
	}
	if(controller->GetStartButton()) isRunning=false;
	if (isRunning){
		shooter->setShooterWheels(Shooter::defaultSpeed);
	}
	else {
		shooter->setShooterWheels(0);
	}

	// Controls shooter loader
	if (controller->GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand)) {
		shooter->setLoader(Shooter::loader::extended);
	}
	if (controller->GetBumperReleased(frc::GenericHID::JoystickHand::kRightHand)) {
		shooter->setLoader(Shooter::loader::retracted);
	}
}
void DoShooter::End(bool interrupted) {
	isRunning = false;
}

DoIntake::DoIntake(Intake* intake) : intake(intake){
   AddRequirements({intake});
}
void DoIntake::Initialize() {
	controller = &Robot::GetRobot()->controller;
}
void DoIntake::Execute() {
	if (controller->GetBumperPressed(frc::GenericHID::JoystickHand::kLeftHand)) {
		isRunning=!isRunning;
	}
	if(controller->GetStartButton()){
		isRunning=false;
		intake->setIntake(Intake::intake_mode::reverse);
	} 
	else{
		if(isRunning){
			intake->setIntake(Intake::intake_mode::intake);
		}
		else {
			intake->setIntake(Intake::intake_mode::off);
		}
	}
	if(controller->GetStartButtonReleased()) intake->setIntake(Intake::intake_mode::off);
}
void DoIntake::End(bool interrupted) {
	isRunning = false;
}
/* bool CheckJoystickForInterrupt()
** Returns true if any input is pressed on the controller, ending the command
*/ 
bool CheckJoystickForInterrupt() {
	frc::XboxController* controller = &Robot::GetRobot()->controller;
	return (controller->GetBackButton()
	|| controller->GetBumper(frc::GenericHID::JoystickHand::kRightHand)
	|| controller->GetBumper(frc::GenericHID::JoystickHand::kLeftHand)
	|| controller->GetStartButton() 
	|| controller->GetStickButton(frc::GenericHID::JoystickHand::kRightHand)
	|| controller->GetStickButton(frc::GenericHID::JoystickHand::kLeftHand) 
	|| fabs(controller->GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand)) > .3
	|| fabs(controller->GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand)) > .3
	|| fabs(controller->GetX(frc::GenericHID::JoystickHand::kLeftHand)) > .3
	|| fabs(controller->GetY(frc::GenericHID::JoystickHand::kLeftHand)) > .3
	|| fabs(controller->GetX(frc::GenericHID::JoystickHand::kRightHand)) > .3
	|| fabs(controller->GetY(frc::GenericHID::JoystickHand::kRightHand)) > .3
	);
}

void MagicalGarbage::Initialize(){
	controller = &Robot::GetRobot()->controller;
	std::cout << "The magical garbage has initialized." << std::endl;
}
void MagicalGarbage::Execute(){
	if(controller->GetAButtonPressed()){
		std::cout << "POV Toggle" << std::endl;
		Robot::GetRobot()->togglePOV();
	}
}
}