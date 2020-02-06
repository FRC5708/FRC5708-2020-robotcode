/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/IntakeCommand.h"

IntakeCommand::IntakeCommand() {
}

void IntakeCommand::Initialize() {
	startTime = std::chrono::steady_clock::now();
}
void IntakeCommand::Execute() {
    //TODO: Start feed motors
}
bool IntakeCommand::IsFinished() {
    if (std::chrono::steady_clock::now() > startTime + std::chrono::milliseconds(2000)) {
		//TODO: Stop feed motors
		return true;
	}
	return false;
}