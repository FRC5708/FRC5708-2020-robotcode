#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>

#include "DIOMaps.h"

class Intake : protected frc2::SubsystemBase {
private:
    frc::SpeedController* const intakeMotor = new frc::Victor(IntakeMotorChannel);
    frc::SpeedController* const magazineMotor = new frc::Victor(IntakeMotorChannel);
public:
	Intake(){};
    enum intake_mode{intake,off,reverse};
	void setIntake(intake_mode mode);
};