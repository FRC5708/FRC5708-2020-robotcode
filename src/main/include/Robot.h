/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/Joystick.h>
#include <frc2/command/button/JoystickButton.h>
#include <frc/XboxController.h>

#include "subsystems/Drivetrain.h"
#include "commands/DriveWithJoystick.h"
#include "subsystems/VisionReceiver.h"
#include "commands/AutoDrive.h"

extern const bool IS_PROD;


class Robot : public frc::TimedRobot {
 public:
	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	void TestInit() override;
	static Robot* GetRobot();
	frc::Joystick DriveJoystick{0};

	Drivetrain drivetrain;
	VisionReceiver visionReceiver;

	int testing_tick_counter = 0;
	DriveWithJoystick driveCommand;
	AutoDrive autoDrive;
 private:
	frc2::Command* m_autonomousCommand = nullptr;
};
