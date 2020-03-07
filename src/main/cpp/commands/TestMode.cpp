#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include "commands/TestMode.h"
#include "Control.h"



namespace TestingCommands {
    Drivetrain* drivetrain = Drivetrain::getDrivetrain();
    Intake* intake = Intake::getIntake();
    Odometry* odometry = Odometry::getOdometry();
    Shooter* shooter = Shooter::getShooter();
    frc::XboxController* controller = Control::controller;
    std::chrono::steady_clock test_clock;
    std::chrono::steady_clock::time_point test_command_start_time;
    namespace DrivetrainTestingCommands {
        TestDriveForward::TestDriveForward() {
            AddRequirements(drivetrain);
        }
        void TestDriveForward::Initialize() {
            test_clock.now() = test_command_start_time;
        }
        void TestDriveForward::Execute() {
            drivetrain->Drive(0.3, 0.3);
        }
        bool TestDriveForward::IsFinished() {
            return test_clock.now() - test_command_start_time > std::chrono::seconds(2);
        }
        void TestDriveForward::End(bool interrupted) {
            drivetrain->Drive(0, 0);
        }
        TestJoystickYValue::TestJoystickYValue() {
            AddRequirements(drivetrain);
        }
        void TestJoystickYValue::Initialize() {
            test_clock.now() = test_command_start_time;
        }
        void TestJoystickYValue::Execute() {
            if ((test_clock.now() - test_command_start_time) % std::chrono::milliseconds(50) == std::chrono::milliseconds(0)) {
                std::cout << controller->GetY(frc::GenericHID::JoystickHand::kLeftHand) << std::endl;
            }
        }
        bool TestJoystickYValue::IsFinished() {
            return test_clock.now() - test_command_start_time > std::chrono::seconds(5);
        }
        void TestJoystickYValue::End(bool interrupted) {
            drivetrain->Drive(0, 0);
        }   
    }
}
/*void SOMETHING::Initialize() {
    drivetrain_sendablechooser.SetDefaultOption("None", 0);
    drivetrain_sendablechooser.AddOption("ACTIVATES MOTORS - Test driving motors forward", 1);
    drivetrain_sendablechooser.AddOption("ACTIVATES MOTORS - Test the Y value of the Xbox controller", 2);
    frc::SmartDashboard::PutData("Drivetrain Tests", &drivetrain_sendablechooser);
}
//SmartDashboard::PutData("ElevatorMove: up", new ElevatorMove(2.7));
*/