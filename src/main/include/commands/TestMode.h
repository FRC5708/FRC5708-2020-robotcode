#pragma once

#include <chrono>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Intake.h"
#include "subsystems/Shooter.h"
#include "subsystems/Odometry.h"

namespace TestingCommands{
    extern Drivetrain* drivetrain;
    extern Intake* intake;
    extern Odometry* odometry;
    extern Shooter* shooter;
    extern std::chrono::steady_clock test_clock;
    extern std::chrono::steady_clock::time_point test_command_start_time;
    namespace DrivetrainTestingCommands{
        class TestDriveForward : public frc2::CommandHelper<frc2::CommandBase,TestDriveForward>{
            void Initialize() override;
            void Execute() override;
            bool IsFinished() override;
            void End(bool interrupted) override;
        public:
            TestDriveForward();


        };
        class TestJoystickYValue : public frc2::CommandHelper<frc2::CommandBase,TestJoystickYValue>{

        };
    }
    namespace IntakeTestingCommands{

    }
    namespace OdometryTestingCommands{
        class ReturnPose2D : public frc2::CommandHelper<frc2::CommandBase,ReturnPose2D>{

        };
    }
    namespace ShooterTestingCommands{
        class ReturnShooterMotorPowers : public frc2::CommandHelper<frc2::CommandBase,ReturnShooterMotorPowers>{

        };
    }

    using namespace DrivetrainTestingCommands;
    
    class DrivetrainTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,DrivetrainTests> {
        //WHEN IMPLEMETING THIS IN Drivetrain.cpp PUT THIS IN A FUNCTION THERE :)
        //AddRequirements(drivetrain);
        //AddCommands();
    };
    class IntakeTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,IntakeTests> {
        //AddRequirements(intake);
        //AddCommands();
    };
    class OdometryTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,OdometryTests>{
        //AddRequirements(odometry);
        //AddCommands();
    };
    class ShooterTests : public frc2::CommandHelper<frc2::SequentialCommandGroup,ShooterTests>{
        //AddRequirements(shooter);
        //AddCommands();
    };
}