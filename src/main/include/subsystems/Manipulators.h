#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>

#include "DIOMaps.h"

class Manipulators : protected frc2::SubsystemBase {
	private:
	TalonSRX* SRMotor = new TalonSRX(RightShooterMotorChannel);
    TalonSRX* SLMotor = new TalonSRX(LeftShooterMotorChannel);
    frc::SpeedController* SCMotor = new frc::Victor(ShooterCAMChannel);
    frc::SpeedController* const IMotor = new frc::Victor(IntakeMotorChannel);
    enum Constants {
	    /**
	     * Which PID slot to pull gains from.  Starting 2018, you can choose
	     * from 0,1,2 or 3.  Only the first two (0,1) are visible in web-based configuration.
	     */
	    kSlotIdx = 0,

	    /* Talon SRX/ Victor SPX will supported multiple (cascaded) PID loops.
	     * For now we just want the primary one.
	     */
	    kPIDLoopIdx = 0,

	    /*
	     * set to zero to skip waiting for confirmation, set to nonzero to wait
	     * and report to DS if action fails.
	     */
	    kTimeoutMs = 30
    };
	public:
	Manipulators();
    void ManipInit();
	void SetShooterWheels(int);
    void SetShooterCAM(int);
    void SetIntakeWheels(int);
};