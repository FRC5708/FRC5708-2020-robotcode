#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

namespace TestingCommands{
    namespace DrivetrainTestingCommands{
        class TestDriveForward : public frc2::CommandHelper<frc2::CommandBase,TestDriveForward>{

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
        //AddCommands();
    };
}