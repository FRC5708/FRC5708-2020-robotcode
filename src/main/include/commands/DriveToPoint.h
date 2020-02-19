#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include "subsystems/Drivetrain.h"

class DriveToPoint : public  frc2::CommandHelper<frc2::CommandBase, DriveToPoint> {
    public:
    DriveToPoint();
    void Initialize() override;
    void Execute() override;
    void End();
    bool IsFinished() override;
    private:
    struct point {
        float x;
        float y;
    };
    point position;
    // Distance (in meters) that the robot will stop from the target
    float endDistance = 0.2;
    float heading;
    point destination;
    Drivetrain drive;
};