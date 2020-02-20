#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>

#include "DIOMaps.h"
#include "commands/DriveWithJoystick.h"

class Intake : public frc2::SubsystemBase {
private:
    frc::SpeedController* const intakeMotor = new frc::Victor(IntakeMotorChannel);
    frc::SpeedController* const magazineMotor = new frc::Victor(MagazineMotorChannel);
    
public:
	Intake();
    enum intake_mode{intake,off,reverse};
	void setIntake(intake_mode mode);
};