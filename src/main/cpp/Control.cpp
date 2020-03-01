#include "Control.h"
#include <iostream>

namespace Control{
    namespace{
        //Anonymous namespace to avoid directly setting state
        POV robotPOV = ShooterPOV;
    }
    void togglePOV(){
        if(robotPOV==POV::IntakePOV) robotPOV=POV::ShooterPOV;
        else robotPOV=POV::IntakePOV;
        //TODO: Send control message to pi, so that some sort of POV indicator shows up on the stream?
        std::cout << "POV switched to " << (robotPOV==POV::IntakePOV ? "Intake" : "Shooter")<< std::endl;
    }
    extern frc::XboxController* controller=new frc::XboxController(0);
    POV getPOV(){return robotPOV;}
    
}