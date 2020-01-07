#include "subsystems/ColorVision.h"
#include <iostream>
/*
* Boring test code (untested, though!) for the color sensor.
* Documentation: http://www.revrobotics.com/content/sw/color-sensor-v3/sdk/docs/cpp/index.html
* Sample Code: https://github.com/REVrobotics/Color-Sensor-v3-Examples/blob/master/C%2B%2B/Read%20RGB%20Values/src/main/cpp/Robot.cpp
* Product Page: http://www.revrobotics.com/rev-31-1557/
* Note that building this code requires downloading the sdk at http://revrobotics.com/content/sw/color-sensor-v3/sdk/Color-Sensor-V3-SDK-v1.0.0.zip
*/

ColorVision::ColorVision(){
    //Possibly change calibration values here?
}
void ColorVision::Periodic(){
    if(ENABLE_COLOR_VISION_LOGGING){
        auto detectedColor = colorSensor.GetRawColor();
        std::cout << "Red: " << detectedColor.red << std::endl;
        std::cout << "Blue: " << detectedColor.blue << std::endl;
        std::cout << "Green: " << detectedColor.green << std::endl;
        uint32_t proximity = colorSensor.GetProximity();
        std::cout << "Proximity: " << proximity << std::endl;
    }
}