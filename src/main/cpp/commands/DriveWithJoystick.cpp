#include <iostream>

#include <frc2/command/CommandHelper.h>

#include "commands/DriveWithJoystick.h"

// buttons on xbox:
// 1=A, 2=B, 3=X, 4=Y, 5=left bumper, 6=right bumper, 7=Back, 8=Start, 9=left joystick, 10=right joystick


// constexpr int INTAKE_BUTTON = 5, 🤖 = 6;

using namespace DriveWithJoystick;

frc::XboxController controller = frc::XboxController(0);

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

// TODO: CancelCommand (Requires CommandGroup, which does not exist currently)

// Setup for joystick-activated commands go here (lift controls, manipulators, ect.)

DoDrivetrain::DoDrivetrain(Drivetrain* drivetrain) : drivetrain(drivetrain){
   AddRequirements({drivetrain});
}
void DoDrivetrain::Execute() {
	double turn = 0;
	double power = 0;

	turn = -controller.GetX(frc::GenericHID::JoystickHand::kLeftHand);
	power = controller.GetTriggerAxis(frc::GenericHID::JoystickHand::kRightHand)-controller.GetTriggerAxis(frc::GenericHID::JoystickHand::kLeftHand);
	turn = inputTransform(turn, 0, 0.1);

	power = inputTransform(power, 0.15, 0.03);

    // Auton stuff

/* 	if (Robot::autoDrive.commandUsing != nullptr) {
		if (fabs(power) < 0.3 && fabs(turn) < 0.3) return;
		else {
			std::cout << "cancelling auto drive" << std::endl;
			cancelCommand(Robot::autoDrive.commandUsing);
		} 
	} */

	//Robot::drivetrain.DrivePolar(power, turn);
	double v = (1-fabs(turn)) * (power) + power;
	double w = (1-fabs(power)) * (turn) + turn;
	double right = (v+w)/2;
	double left = (v-w)/2;
	
	//powerRampup(left, &currentLeftPower);
	//powerRampup(right, &currentRightPower);
	
	drivetrain->Drive(left, right);
}
void DoDrivetrain::End() {
	drivetrain->Drive(0, 0);
}

DoShooter::DoShooter(Shooter* shooter) : shooter(shooter){
   AddRequirements({shooter});
}
void DoShooter::Execute() {

	// Controls shooting wheels
	if (controller.GetXButtonReleased()) {
		if (!pressed){
			pressed = true;
			shooter->setShooterWheels(16);
		}
		else {
			pressed = false;
			shooter->setShooterWheels(0);
		}
	}

	// Controls shooter loader
	if (controller.GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand)) {
		shooter->setLoader(Shooter::loader::extended);
	}
	if (controller.GetBumperReleased(frc::GenericHID::JoystickHand::kRightHand)) {
		shooter->setLoader(Shooter::loader::retracted);
	}
}

DoIntake::DoIntake(Intake* intake) : intake(intake){
   AddRequirements({intake});
}
void DoIntake::Execute() {
	if (controller.GetBumperPressed(frc::GenericHID::JoystickHand::kRightHand)) {
		intake->setIntake(Intake::intake_mode::intake);
	}
	if (controller.GetBumperReleased(frc::GenericHID::JoystickHand::kRightHand)) {
		intake->setIntake(Intake::intake_mode::off);
	}
}
