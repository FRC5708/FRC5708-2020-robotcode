#pragma once

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/SequentialCommandGroup.h>

/* class ShootCommand : public frc2::CommandHelper<frc2::CommandBase, DriveWithJoystick> 
**  
**/
class ShootCommand : public frc2::CommandHelper<frc2::SequentialCommandGroup,ShootCommand> {
    ShootCommand(double power=1.0);
};
 