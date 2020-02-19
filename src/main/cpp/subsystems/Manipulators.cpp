#include "subsystems/Manipulators.h"

Manipulators::Manipulators() {
}

void Manipulators::ManipInit() {
    SRMotor->ConfigFactoryDefault();
    /* first choose the sensor */
	SRMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
	SRMotor->SetSensorPhase(true);

	/* set the peak and nominal outputs */
	SRMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	SRMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	SRMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	SRMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);
	/* set closed loop gains in slot0 */
	SRMotor->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
	SRMotor->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	SRMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	SRMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);

    SLMotor->ConfigFactoryDefault();
    /* first choose the sensor */
	SLMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::CTRE_MagEncoder_Relative, 0, kTimeoutMs);
	SLMotor->SetSensorPhase(true);
    
	/* set the peak and nominal outputs */
	SLMotor->ConfigNominalOutputForward(0, kTimeoutMs);
	SLMotor->ConfigNominalOutputReverse(0, kTimeoutMs);
	SLMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	SLMotor->ConfigPeakOutputReverse(-1, kTimeoutMs);
	/* set closed loop gains in slot0 */
	SLMotor->Config_kF(kPIDLoopIdx, 0.1097, kTimeoutMs);
	SLMotor->Config_kP(kPIDLoopIdx, 0.22, kTimeoutMs);
	SLMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	SLMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
}
void Manipulators::SetShooterWheels(int power) {
    SRMotor->Set(TalonSRXControlMode::Velocity,power);
    SLMotor->Set(TalonSRXControlMode::Velocity,power);
}

void Manipulators::SetShooterCAM(int power) {
    SCMotor->Set(TalonSRXControlMode::PercentOutput,power);
}

void Manipulators::SetIntakeWheels(int power) {
    IMotor->Set(power);
}
