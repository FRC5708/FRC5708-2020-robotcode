/*----------------------------------------------------------------------------*/
/* Copyright (c) 2018 FIRST. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

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
//Subsystems
Drivetrain* const Robot::drivetrain = new Drivetrain();

void Robot::RobotInit() {}

void Robot::AutonomousInit() {}
void Robot::AutonomousPeriodic() {}

void Robot::TeleopInit() {}
void Robot::TeleopPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
