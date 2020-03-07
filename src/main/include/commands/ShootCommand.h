#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>
#include <chrono>

#include "subsystems/Shooter.h"

class Shooter; //Defined in subsystems/Shooter.h


class ShootCommand : public frc2::CommandHelper<frc2::SequentialCommandGroup,ShootCommand> {
public:
    ShootCommand(double power=Shooter::defaultSpeed);
private:
    double shooterSpeed;
    
    bool shootingStarted = false;
    std::chrono::steady_clock::time_point shootStartTime;
    
    void Execute() override;
	bool IsFinished() override;
    void End(bool interrupted) override;
};
 