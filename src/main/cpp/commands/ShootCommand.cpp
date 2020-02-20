#include "commands/ShootCommand.h"
#include "Robot.h"

ShootCommand::ShootCommand(double power){
   AddRequirements(&Robot::GetRobot()->shooter);
   
    //TODO: FIXME!
    //TODO: IMPLEMENT ME!
}