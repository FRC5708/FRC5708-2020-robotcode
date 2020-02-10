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

#include <iostream>
#include <sys/stat.h>
#include <chrono>

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
void Robot::DisabledInit() {}

void Robot::DisabledPeriodic() {}


void Robot::AutonomousInit() {

	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Schedule();
	}
}

void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {
	// This makes sure that the autonomous stops running when
	// teleop starts running. If you want the autonomous to
	// continue until interrupted by another command, remove
	// this line or comment it out.
	if (m_autonomousCommand != nullptr) {
		m_autonomousCommand->Cancel();
		m_autonomousCommand = nullptr;
	}

	driveCommand.Schedule();
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}




//TESTING THINGS

void Robot::TestInit() {
testing_tick_counter = 0;
TestingTime = std::chrono::steady_clock::now();
} 

//This function is called periodically during test mode.
void Robot::TestPeriodic() {
	//TODO: this is going to be replaced with a toggle eventually, hopefully
	if (true) {
		//checks if 3 seconds have passed since Robot::TestInit was run
		if (std::chrono::steady_clock::now() < TestingTime + std::chrono::milliseconds((int) (3000))) {
			Robot::GetRobot()->drivetrain.Drive(0.3, 0.3);
			//runs once when 2 seconds have passed
			if (std::chrono::steady_clock::now() == TestingTime + std::chrono::milliseconds((int) (2000))) {
				std::vector<double> vect= Robot::GetRobot()->drivetrain.getMotorPowers();
				// CURRENT PROBLEM - cant figure out how to correctly refrence the encoder in it's class...
				std::cout << "FL Check: " << (((vect.at(0) > 0.1) && (drivetrain.leftEncoder -> GetDistance() > 1))? "Good :)" : "BAD!!!!") << ", FR Check: " << (((vect.at(1) > 0.1) && (drivetrain.rightEncoder -> GetDistance() > 1)) ? "Good :)" : "BAD!!!!") << ", BL Check: " << (((vect.at(2) > 0.1) && (drivetrain.leftEncoder -> GetDistance() > 1)) ? "Good :)" : "BAD!!!!") << ", BR Check: " << (((vect.at(3) > 0.1) && (drivetrain.rightEncoder -> GetDistance() > 1)) ? "Good :)" : "BAD!!!!");
				}
			}
		}
	//TODO: this is going to be replaced with a toggle eventually
	if (false) {
		Robot::GetRobot()->drivetrain.Drive(0.3, 0.3);
	}

	//TODO: this is going to be replaced with a toggle eventually
	if (false) {	
		// counts so that it activates every half second
		testing_tick_counter++ ;
		if (testing_tick_counter %25 == 0) {
			std::vector<double> vect=Robot::GetRobot()->drivetrain.getMotorPowers();
			std::cout << "FL: " << vect.at(0) << "| FR: " << vect.at(1) << "| BL: " << vect.at(2) << "| BR: " << vect.at(3);
		}
	}
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

/**
 * 
 * DONT WORRY ABOUT IT, ILL FIRGURE THIS PART OUT EVENTUALLY...
//calls value
 AutonMode primary_objective = (AutonMode) primary_objective_select.GetSelected();

//something
 void setupObjectiveChooser(frc::SendableChooser<AutonMode>* chooser, std::string name) {

	// space in beginning for alphabetical ordering
	chooser->AddDefault(" " + name + " default: Cross line", AutonMode::crossLine);
	chooser->AddObject("do nothing", AutonMode::nothing);
	chooser->AddObject("Switch (either)", AutonMode::eitherSwitch);
	chooser->AddObject("Switch (left)", AutonMode::leftSwitch);
	chooser->AddObject("Switch (right)", AutonMode::rightSwitch);
	chooser->AddObject("Switch (side)", AutonMode::sideSwitch);
	//chooser->AddObject("Scale (either)", AutonMode::eitherScale);
	//chooser->AddObject("Scale (left)", AutonMode::leftScale);
	//chooser->AddObject("Scale (right)", AutonMode::rightScale);
	frc::SmartDashboard::PutData(name, chooser);

//something
frc::SendableChooser<AutonMode> primary_objective_select;

//something
enum struct test_options {




}

encoders and motors are the same direction
kinematics

encoder object - get distance


frc::Encoder* const leftEncoder = new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1]);
	frc::Encoder* const rightEncoder = new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1]);
*/