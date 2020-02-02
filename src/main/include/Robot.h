/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include "RobotMap.h"
#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/Joystick.h>

#include "subsystems/Drivetrain.h"
#include "commands/DriveWithJoystick.h"
#include "subsystems/ColorVision.h"

extern const bool IS_PROD;


class Robot : public frc::TimedRobot {
 public:
	static ColorVision colorVision;
	void RobotInit() override;
	void RobotPeriodic() override;
	void DisabledInit() override;
	void DisabledPeriodic() override;
	void AutonomousInit() override;
	void AutonomousPeriodic() override;
	void TeleopInit() override;
	void TeleopPeriodic() override;
	void TestPeriodic() override;
	static Robot* GetRobot();
	frc::Joystick DriveJoystick{0};
	Drivetrain drivetrain;
	DriveWithJoystick driveCommand;
 private:
	frc2::Command* m_autonomousCommand = nullptr;
};
