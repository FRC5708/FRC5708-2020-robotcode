#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Odometry.h"

class DriveToPoint : public  frc2::CommandHelper<frc2::CommandBase, DriveToPoint> {
public:
    DriveToPoint();
    void Initialize() override;
    void Execute() override;
    void End();
    bool IsFinished() override;
    
    frc::Translation2d targetPoint;
private:
    frc::Translation2d startingPoint;
    
    // Distance (in meters) that the robot will stop from the target
    static constexpr units::meter_t endDistance{0.2};
    
    Drivetrain* drivetrain;
    Odometry* odometry;
};