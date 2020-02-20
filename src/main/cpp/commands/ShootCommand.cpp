#include "commands/ShootCommand.h"
#include "Robot.h"

ShootCommand::ShootCommand(double power){
   // AddRequirements(Robot::GetRobot()->shooter);

   std::initializer_list<frc2::Subsystem*> requirements {
       &Robot::GetRobot()->shooter
    };

   AddRequirements(requirements);
    //TODO: FIXME!
    //TODO: IMPLEMENT ME!
}