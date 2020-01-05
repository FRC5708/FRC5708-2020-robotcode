/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

#include <frc/smartdashboard/SmartDashboard.h>
#include <frc2/command/CommandScheduler.h>

#include <iostream>
#include <sys/stat.h>

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

void Robot::RobotInit() {}

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
}

/**
 * This function is called periodically during operator control.
 */
void Robot::TeleopPeriodic() {}

/**
 * This function is called periodically during test mode.
 */
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
