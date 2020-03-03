/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2019 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/TimedRobot.h>
#include <frc2/command/Command.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <frc/XboxController.h>
#include <chrono>

#include "commands/DriveWithJoystick.h"
#include "commands/TurnToAngle.h"
#include "commands/Autonomous.h"
#include "DebugValues.h"
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Odometry.h"
#include "subsystems/Shooter.h"
#include "subsystems/VisionReceiver.h"

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
    
	VisionReceiver visionReceiver; //Requires nothing to be initialized.
	Drivetrain drivetrain;
	Odometry odometry;
	Intake intake;
	Shooter shooter;

	int testing_tick_counter = 0;
	bool testing_first_motor_test = true;
	
	DriveWithJoystick::InterruptableByController<VisionDrive> visionDrive;
	std::chrono::steady_clock::time_point TestingTime;
	std::chrono::steady_clock::time_point MotorTestStartTime;
	frc::SendableChooser<char> TestToRun;
	frc::SendableChooser<bool> OutputMotorValues;
	DriveWithJoystick::MagicalGarbage povSwitcher;
 private:
	AutonomousCommand autonomous;
};