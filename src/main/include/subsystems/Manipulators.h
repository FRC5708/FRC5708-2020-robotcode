#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Victor.h>
#include <frc/Encoder.h>

#include "DIOMaps.h"

class Manipulators : protected frc2::SubsystemBase {
	private:
	frc::SpeedController* const SRMotor = new frc::Victor(RightShooterMotorChannel);
    frc::SpeedController* const SLMotor = new frc::Victor(LeftShooterMotorChannel);
    frc::SpeedController* const SCMotor = new frc::Victor(ShooterCAMChannel);
    frc::SpeedController* const IMotor = new frc::Victor(IntakeMotorChannel);
	public:
	Manipulators();
	void SetShooterWheels(int);
    void SetShooterCAM(int);
    void SetIntakeWheels(int);
};