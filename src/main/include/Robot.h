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
#include <frc/smartdashboard/SendableChooser.h>
#include <chrono>

#include "subsystems/Drivetrain.h"
#include <frc/interfaces/Gyro.h>
#include <frc/AnalogGyro.h>
#include <frc/ADXRS450_Gyro.h>
#include "subsystems/Intake.h"
#include "commands/DriveWithJoystick.h"
#include "subsystems/Shooter.h"
#include "subsystems/Intake.h"
#include "subsystems/VisionReceiver.h"
#include "commands/VisionDrive.h"
#include "subsystems/Odometry.h"

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
	
	frc::XboxController controller = frc::XboxController(0);
	
	Drivetrain drivetrain;
	Shooter shooter;
	Intake intake;
	
	Odometry odometry; // MUST be declared after drivetrain
    
	VisionReceiver visionReceiver;

	int testing_tick_counter = 0;
	bool testing_first_motor_test = true;
	
	VisionDrive autoDrive;
	std::chrono::steady_clock::time_point TestingTime;
	std::chrono::steady_clock::time_point MotorTestStartTime;
	frc::SendableChooser<char> TestToRun;
	frc::SendableChooser<bool> OutputMotorValues;
 private:
	frc2::Command* m_autonomousCommand = nullptr;
};