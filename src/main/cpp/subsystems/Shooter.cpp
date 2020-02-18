#include "subsystems/shooter.h"

Shooter::Shooter(){
	//TODO: The configuration values used here are almost certainly wrong. Check me!
	rightShooterMotor->ConfigFactoryDefault();
    /* first choose the sensor */
	rightShooterMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
	rightShooterMotor->SetSensorPhase(true);

	/* set the peak and nominal outputs */
	rightShooterMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	rightShooterMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	rightShooterMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	rightShooterMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);
	/* set closed loop gains in slot0 */
	rightShooterMotor->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
	rightShooterMotor->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	rightShooterMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	rightShooterMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

    leftShooterMotor->ConfigFactoryDefault();
	/* first choose the sensor */
	leftShooterMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
	leftShooterMotor->SetSensorPhase(true);
    
	/* set the peak and nominal outputs */
	leftShooterMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	leftShooterMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	leftShooterMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	leftShooterMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);
	/* set closed loop gains in slot0 */
	leftShooterMotor->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
	leftShooterMotor->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	leftShooterMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	leftShooterMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
}
void Shooter::setShooterWheels(double velocity){
	rightShooterMotor->Set(TalonSRXControlMode::Velocity,velocity);
	leftShooterMotor->Set(TalonSRXControlMode::Velocity,velocity);
}
void Shooter::setLoader(loader position){
	//TODO: IMPLEMENT ME!
	return;
} 