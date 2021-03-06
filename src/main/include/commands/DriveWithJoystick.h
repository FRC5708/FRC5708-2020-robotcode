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
			Intake* intake; //Initialized within member initialization list
			frc::XboxController* controller; //Initialized within member initialization list
			bool isRunning=false;

			void Execute() override;
			void End(bool interrupted) override;
		public:
			DoIntake(Intake* intake);
	};
	class DoShooter : public frc2::CommandHelper<frc2::CommandBase,DoShooter>{
		private:
			Shooter* shooter; //Initialized within member initialization list
			frc::XboxController* controller; //Initialized within member initialization list

			void Execute() override;
			bool isRunning = false;
			void End(bool interrupted) override;
		public:
			DoShooter(Shooter* shooter);
	};
	class DoDrivetrain : public frc2::CommandHelper<frc2::CommandBase,DoDrivetrain>{
		private:
			Drivetrain* drivetrain; //Initialized within member initialization list
			frc::XboxController* controller; //Initialized within member initialization list

			double creepRate=0.25; //The slowdown multiplier while holding the creep button.
			void Execute() override;
			void End(bool interrupted) override;
		public:
			DoDrivetrain(Drivetrain* drivetrain);
	};
	class MagicalGarbage : public frc2::CommandHelper<frc2::CommandBase,MagicalGarbage>{
		//Because Triggers are just straight-up broken in c++.
		private:
			frc::XboxController* controller;
			void Execute() override;
		public:
			MagicalGarbage();
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