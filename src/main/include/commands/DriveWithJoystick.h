/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc/XboxController.h>

class Intake; // Defined within subsystems/Intake.h
class Shooter; // Defined within subsystems/Shooter.h
class Drivetrain; // Defined within subsystems/Drivetrain.h

namespace DriveWithJoystick{
	class DoIntake : public frc2::CommandHelper<frc2::CommandBase,DoIntake>{
		private:
			frc2::XboxController* controller;
			Intake* intake;
			void Execute() override;
		public:
			DoIntake(Intake* intake);
	};
	class DoShooter : public frc2::CommandHelper<frc2::CommandBase,DoIntake>{
		private:
			frc2::XboxController* controller;
			Shooter* shooter;
			void Execute() override;
			bool pressed = false;
		public:
			DoShooter(Shooter* shooter);
	};
	class DoDrivetrain : public frc2::CommandHelper<frc2::CommandBase,DoIntake>{
		private:
			frc2::XboxController* controller;
			Drivetrain* drivetrain;
			void Execute() override;
			void End(); 
		public:
			DoDrivetrain(Drivetrain* drivetrain);
	};
	
	
	bool CheckJoystickForInterrupt();
	template<class T, 
	typename = std::enable_if_t<std::is_base_of_v<frc2::Command, T>>>
	class InterruptableByController : public T {
		protected:
		bool IsFinished() override {
			return T::IsFinished() || CheckJoystickForInterrupt();
		}
	};
}