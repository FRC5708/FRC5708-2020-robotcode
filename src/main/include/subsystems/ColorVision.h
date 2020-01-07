#pragma once

#include <frc2/command/SubsystemBase.h>
#include "rev/ColorSensorV3.h"
#include "../RobotMap.h"

class ColorVision : protected frc2::SubsystemBase {
private:
    rev::ColorSensorV3 colorSensor{(frc::I2C::Port) I2CPORT};
public:
    ColorVision();
    void Periodic();
};