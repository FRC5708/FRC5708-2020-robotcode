/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/Joystick.h>
#include <frc/XboxController.h>
#include "subsystems/Manipulators.h"



class DriveWithJoystick : public  frc2::CommandHelper<frc2::CommandBase, DriveWithJoystick> {
public:
	frc::XboxController controller = frc::XboxController(0);
	DriveWithJoystick();
	void doIntake();
	void doShooter();
	void doDrivetrain();
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override;
	void End();
private:
	bool pressed = false;
	Manipulators manipulator;
};