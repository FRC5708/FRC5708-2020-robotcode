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
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Shooter.h"

class Intake; // Defined within subsystems/Intake.h
class Shooter; // Defined within subsystems/Shooter.h
class Drivetrain; // Defined within subsystems/Drivetrain.h

namespace DriveWithJoystick{
	class DoIntake : public frc2::CommandHelper<frc2::CommandBase,DoIntake>{
		private:
			Intake* intake;
			void Execute() override;
		public:
			DoIntake(Intake* intake);
	};
	class DoShooter : public frc2::CommandHelper<frc2::CommandBase,DoIntake>{
		private:
			Shooter* shooter;
			void Execute() override;
			bool pressed = false;
		public:
			DoShooter(Shooter* shooter);
	};
	class DoDrivetrain : public frc2::CommandHelper<frc2::CommandBase,DoIntake>{
		private:
			Drivetrain* drivetrain;
			void Execute() override;
			void End(); //VScode lies, it does override.
		public:
			DoDrivetrain(Drivetrain* drivetrain);
	};
}