#include "subsystems/Manipulators.h"

// Talons measure speed in encoder ticks per 100 ms
constexpr double speedMultiplier = 256.0*0.1;


Manipulators::Manipulators() {
}

void Manipulators::ConfigShooterMotor(TalonSRX* theMotor) {
	theMotor->ConfigFactoryDefault();
    /* first choose the sensor */
	theMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
	theMotor->SetSensorPhase(true);

	/* set the peak and nominal outputs */
	theMotor->ConfigNominalOutputForward(0.3, kTimeoutMs);
	theMotor->ConfigNominalOutputReverse(-0.3, kTimeoutMs);
	theMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	theMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);
	/* set closed loop gains in slot0 */
	theMotor->Config_kF(kPIDLoopIdx, 0, kTimeoutMs);
	theMotor->Config_kP(kPIDLoopIdx, 100000000, kTimeoutMs);
	theMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	theMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
}

void Manipulators::ManipInit() {
    ConfigShooterMotor(SRMotor);
	ConfigShooterMotor(SLMotor);
	SRMotor->SetInverted(true);
}


void Manipulators::SetShooterWheels(int speed) {
	speed *= speedMultiplier;
    SRMotor->Set(TalonSRXControlMode::Velocity,speed);
    SLMotor->Set(TalonSRXControlMode::Velocity,speed);
}

void Manipulators::SetShooterCAM(int power) {
    SCMotor->Set(TalonSRXControlMode::PercentOutput,power);
}

void Manipulators::SetIntakeWheels(int power) {
    IMotor->Set(power);
}
