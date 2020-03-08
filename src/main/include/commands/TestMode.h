#pragma once

#include <iostream>
#include <chrono>
#include <frc/XboxController.h>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <frc/smartdashboard/SendableChooser.h>

#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Shooter.h"
#include "subsystems/Odometry.h"

namespace TestingCommands{
    void initializeSendableChoosers();

    extern Drivetrain* drivetrain;
    extern Intake* intake;
    extern Odometry* odometry;
    extern Shooter* shooter;
    extern std::chrono::steady_clock test_clock;
    extern std::chrono::steady_clock::time_point test_command_start_time;
    extern frc::XboxController* controller;
    namespace DrivetrainTestingCommands{
        extern frc::SendableChooser<int> drivetrain_sendablechooser;
        class TestDriveForward : public frc2::CommandHelper<frc2::CommandBase,TestDriveForward>{
            void Initialize() override;
            void Execute() override;
            bool IsFinished() override;
            void End(bool interrupted) override;
        public:
            TestDriveForward();
        };
        class TestJoystickYValue : public frc2::CommandHelper<frc2::CommandBase,TestJoystickYValue>{
            void Initialize() override;
            void Execute() override;
            bool IsFinished() override;
            void End(bool interrupted) override;
        public:
            TestJoystickYValue();
        };
    }
    namespace IntakeTestingCommands{
        extern frc::SendableChooser<int> intake_sendablechooser;
        //if state is intake, the first threee should get passed directly, fourth should get held at top, fifth should stop internaly in intake
        //after that point force intake should force motors to run no matter what
    }
    namespace OdometryTestingCommands{
        extern frc::SendableChooser<int> odometry_sendablechooser;
        class ReturnPose2D : public frc2::CommandHelper<frc2::CommandBase,ReturnPose2D>{
        };
    }
    namespace ShooterTestingCommands{
        extern frc::SendableChooser<int> shooter_sendablechooser;
        class ReturnShooterMotorPowers : public frc2::CommandHelper<frc2::CommandBase,ReturnShooterMotorPowers>{
        };
    }

    using namespace DrivetrainTestingCommands;
    
    class DrivetrainTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,DrivetrainTests> {
    public:
        DrivetrainTests();
    private:
        void Initialize() override;
    };
    class IntakeTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,IntakeTests> {

    };
    class OdometryTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,OdometryTests>{

    };
    class ShooterTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,ShooterTests>{

    };
}