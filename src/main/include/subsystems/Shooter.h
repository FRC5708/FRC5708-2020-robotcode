#pragma once

#include <frc2/command/SubsystemBase.h>
#include <frc/Victor.h>
#include <frc/Encoder.h>
#include <ctre/Phoenix.h>

#include "DIOMaps.h"
#include "commands/DriveWithJoystick.h"

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
    kTimeoutMs = 30,
};

class Shooter : public frc2::SubsystemBase {
private:
	TalonSRX* rightShooterMotor = new TalonSRX(RightShooterMotorChannel);
    TalonSRX* leftShooterMotor = new TalonSRX(LeftShooterMotorChannel);
public:
    // rotations per second
    static constexpr double defaultSpeed = 16; // rotations per second
	enum loader{extended,retracted};
	Shooter(); //TODO: CONFIG WITH RIGHT VALUES!
	void setShooterWheels(double velocity);
	void setLoader(loader position); //TODO: IMPLEMENT ME!
    void ConfigureMotor(TalonSRX* theMotor);
};
