/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include "commands/ShooterCommand.h"

ShooterCommand::ShooterCommand() {
}

void ShooterCommand::Initialize() {
	startTime = std::chrono::steady_clock::now();
}
void ShooterCommand::Execute() {
    //TODO: Start shooter motors
}
bool ShooterCommand::IsFinished() {
    if (std::chrono::steady_clock::now() > startTime + std::chrono::milliseconds(2000)) {
		//TODO: Stop shooter motors
		return true;
	}
	return false;
}