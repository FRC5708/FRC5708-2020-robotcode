/*The Control namespace is intended to provide acess to control-related items that don't
** directly interface with the robot.
**This includes items s.a. the controller, driver preferences, and POV state. 
**This is to help avoid much of the clutter within Robot.cpp
*/

#pragma once

#include <frc/XboxController.h>

//TODO: handle driver preferences. 

namespace Control{
    extern frc::XboxController* controller;
    enum POV{ShooterPOV, IntakePOV};
    void togglePOV();
    POV getPOV();
}