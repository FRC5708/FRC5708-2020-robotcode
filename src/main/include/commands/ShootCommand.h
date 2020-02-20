#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

#include "subsystems/Shooter.h"

class Shooter; //Defined in subsystems/Shooter.h


class ShootCommand : public frc2::CommandHelper<frc2::SequentialCommandGroup,ShootCommand> {
    ShootCommand(Shooter* shooter,double power=1.0);
    Shooter* shooter;
};
 