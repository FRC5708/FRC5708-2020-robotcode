#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/SpeedController.h>

#include "commands/DriveWithJoystick.h"

class Intake : public frc2::SubsystemBase {
private:
    frc::SpeedController* const intakeMotor;
    frc::SpeedController* const magazineMotor;
    
public:
	Intake();
    enum intake_mode{intake,off,reverse};
	void setIntake(intake_mode mode);
};