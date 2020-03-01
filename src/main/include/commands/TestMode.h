#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include "subsystems/subsystems.h"

namespace TestingCommands{
    Drivetrain* drivetrain = Drivetrain::getDrivetrain();
    Intake* intake = Intake::getIntake();
    Odometry* odometry = Odometry::getOdometry();
    Shooter* shooter = Shooter::getShooter();
    namespace DrivetrainTestingCommands{
        
        class TestDriveForward : public frc2::CommandHelper<frc2::CommandBase,TestDriveForward>{
        };
        class TestJoystickYValue : public frc2::CommandHelper<frc2::CommandBase,TestJoystickYValue>{

        };
    };
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
        //WHEN IMPLEMETING THIS IN Drivetrain.cpp PUT THIS IN THERE :)
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