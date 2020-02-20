#include "subsystems/shooter.h"

// Talons measure speed in encoder ticks per 100 ms
constexpr double speedMultiplier = 256.0*0.1;


Shooter::Shooter(){
	ConfigureMotor(rightShooterMotor);
	ConfigureMotor(leftShooterMotor);
	rightShooterMotor->SetInverted(true);
}
void Shooter::ConfigureMotor(TalonSRX* theMotor) {
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

void Shooter::setShooterWheels(double speed){
	speed *= speedMultiplier;
	rightShooterMotor->Set(TalonSRXControlMode::Velocity,speed);
	leftShooterMotor->Set(TalonSRXControlMode::Velocity,speed);
}
void Shooter::setLoader(loader position){
	//TODO: IMPLEMENT ME!
	return;
} 