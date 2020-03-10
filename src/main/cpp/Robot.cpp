/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc2/command/CommandScheduler.h>
#include <frc2/command/Command.h>
#include <frc2/command/button/JoystickButton.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include <iostream>
#include <sys/stat.h>
#include <chrono>
#include "subsystems/Odometry.h"

#include <vector>


bool environment_check();
const bool IS_PROD = environment_check(); /*IS_PROD is true if we are running on the production bot.
																					 *This is primarily useful if the test and production bots
																					 *  happen to be using different types of motors/encoders.*/
bool environment_check(){
		//Checks if the file /home/lvuser/platform_test exists. If so, sets IS_PROD to false;
		struct stat buffer;  
		bool IS_PROD_temp = !(stat ("/home/lvuser/platform_test", &buffer) == 0);
		std::cout << "Platform detected as " << (IS_PROD_temp ? "PROD" : "TEST" )<< "..." << std::endl;
		return IS_PROD_temp; 
}

Robot* theRobotInstance;

Robot* Robot::GetRobot() {
	return theRobotInstance;
}

void Robot::RobotInit() {
	theRobotInstance = this;

	if(DEBUG_COMMAND_STATE){
		frc2::CommandScheduler::GetInstance().OnCommandInterrupt(
			[](const frc2::Command& command){
				std::cout << "Command " << command.GetName() << " cancelled." << std::endl;
			}
		);
		frc2::CommandScheduler::GetInstance().OnCommandInitialize(
			[](const frc2::Command& command){
				std::cout << "Command " << command.GetName() << " initialized." << std::endl;
			}
		);
		frc2::CommandScheduler::GetInstance().OnCommandFinish(
			[](const frc2::Command& command){
				std::cout << "Command " << command.GetName() << " finished." << std::endl;
			}
		);
	}

}
/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want to run during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() { frc2::CommandScheduler::GetInstance().Run(); }

/**
 * This function is called once each time the robot enters Disabled mode. You
 * can use it to reset any subsystem information you want to clear when the
 * robot is disabled.
 */
void Robot::DisabledInit() {
}

void Robot::DisabledPeriodic() {}


void Robot::AutonomousInit() {
	Intake::getIntake()->resetBallCounter(); //Resets ball counter to value to START_BALL_COUNT
	// Required because reasons
	autonomous.SetupAuton();
	autonomous.Schedule();
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	autonomous.Cancel();
	povSwitcher.Schedule();
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {
}




//TESTING THINGS
//TODO: add text box that explains what the heck all the sendable chooser boxes mean...
void Robot::TestInit() {
testing_tick_counter = 0;
TestingTime = std::chrono::steady_clock::now();
TestToRun.SetDefaultOption("None", 'N');
TestToRun.AddOption("ACTIVATES MOTORS - Test Motor/Encoder sync", 'M');
TestToRun.AddOption("ACTIVATES MOTORS - Run all wheels forward", 'F');
OutputMotorValues.SetDefaultOption("No", false);
OutputMotorValues.AddOption("Yes", true);
frc::SmartDashboard::PutData("Test To Run", &TestToRun);
frc::SmartDashboard::PutData("Output Motor Values?", &OutputMotorValues);
} 
/*
*This function is called periodically during test mode.
*/
void Robot::TestPeriodic() {
	/*TODO: directly calling drivetrain.Drive will *not* work as intended.
	** Because doDrivetrain is the default command associated with that subsystem, 
	**  manual calls will clash with the values being set by that command.
	** The cleanest way to fix this would be to create a suite of testing commands, 
	**  which Robot::TestInit should instantiate. 
	*/

	//std::cout << "I am not insane." << std::endl;
}
#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif