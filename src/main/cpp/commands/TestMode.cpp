#include "commands/TestMode.h"
#include <frc/shuffleboard/Shuffleboard.h>
#include <chrono>


namespace TestingCommands {
    Drivetrain* drivetrain = Drivetrain::getDrivetrain();
    Intake* intake = Intake::getIntake();
    Odometry* odometry = Odometry::getOdometry();
    Shooter* shooter = Shooter::getShooter();
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
            return  test_clock.now() - test_command_start_time > std::chrono::seconds(2);
        }
        
        void TestDriveForward::End(bool interrupted) {
            drivetrain->Drive(0, 0);
        }
        
    }
}
//SmartDashboard::PutData("ElevatorMove: up", new ElevatorMove(2.7));