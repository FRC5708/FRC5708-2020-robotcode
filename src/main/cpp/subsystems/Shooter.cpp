#include "subsystems/Shooter.h"
#include "subsystems/Intake.h"
#include <ctre/Phoenix.h>
#include "commands/DriveWithJoystick.h"
#include "DIOMaps.h"

// Talons measure speed in encoder ticks per 100 ms
// Encoder ticks based on emperical data
constexpr double speedMultiplier = 1024*0.1;

Shooter shooterInstance;

Shooter::Shooter() : 
	rightShooterMotor(new WPI_TalonSRX(RightShooterMotorChannel)),
    leftShooterMotor(new WPI_TalonSRX(LeftShooterMotorChannel)),
	loader(9) {
		
	loader.SetBounds(2.5, 0, 0, 0, 0.5);
	
	ConfigureMotor(rightShooterMotor);
	ConfigureMotor(leftShooterMotor);
	rightShooterMotor->SetInverted(true);

	SetDefaultCommand(DriveWithJoystick::DoShooter(this));
	assert(this == &shooterInstance); // there should only be one instance.
	if(DEBUG_CONSTRUCTORS) std::cout << "Shooter initialized." << std::endl;
}
Shooter* Shooter::getShooter(){
	return &shooterInstance;
}
void Shooter::ConfigureMotor(WPI_TalonSRX* theMotor) {
	theMotor->ConfigFactoryDefault();
    /* first choose the sensor */
	theMotor->ConfigSelectedFeedbackSensor(FeedbackDevice::QuadEncoder, 0, kTimeoutMs);
	theMotor->SetSensorPhase(true);

	// Must be in coast mode for bang-bang control to function
	theMotor->SetNeutralMode(NeutralMode::Coast);

	/* set the peak and nominal outputs */
	theMotor->ConfigNominalOutputForward(0.3, kTimeoutMs);
	theMotor->ConfigNominalOutputReverse(0.3, kTimeoutMs);
	theMotor->ConfigPeakOutputForward(1, kTimeoutMs);
	theMotor->ConfigPeakOutputReverse(0, kTimeoutMs);
	/* set closed loop gains in slot0 */
	theMotor->Config_kF(kPIDLoopIdx, 0, kTimeoutMs);
	// Very large P value has effect of applying minimum power when going faster than set speed, and maximum when going slower.
	theMotor->Config_kP(kPIDLoopIdx, 100, kTimeoutMs);
	theMotor->Config_kI(kPIDLoopIdx, 0.0, kTimeoutMs);
	theMotor->Config_kD(kPIDLoopIdx, 0.0, kTimeoutMs);
}

void Shooter::setShooterWheels(double speed){
	if (speed == 0) {
		rightShooterMotor->Set(TalonSRXControlMode::Disabled, 0);
		leftShooterMotor->Set(TalonSRXControlMode::Disabled, 0);
	}
	else {	
		speed *= speedMultiplier;
		rightShooterMotor->Set(TalonSRXControlMode::Velocity,speed);
		leftShooterMotor->Set(TalonSRXControlMode::Velocity,speed);
		//rightShooterMotor->Set(TalonSRXControlMode::PercentOutput, 1);
		//leftShooterMotor->Set(TalonSRXControlMode::PercentOutput, 1);
	}
}


bool Shooter::isSpunTo(double speed) {
	return ((rightShooterMotor->GetSelectedSensorVelocity() / speedMultiplier) / speed >= 0.95
	&& (leftShooterMotor->GetSelectedSensorVelocity() / speedMultiplier) / speed >= 0.95);
}

void Shooter::setLoader(loaderPos position) {
	switch (position) {
		case loaderPos::extended: 
			loader.Set(1); break;
		case loaderPos::retracted:
			loader.Set(0); break;
		default:
			abort();
	};
	
	if(DEBUG_LOADER_STATE) std::cout << "Loader position set to " << (position==loaderPos::extended ? "extended" : "retracted") << std::endl;
	if(position==loaderPos::extended){
		Intake::getIntake()->decrementBallCounter();
	}
} 

void Shooter::toggleLoader(){
	//Toggle the loader state
	if(loader_state==loaderPos::extended) loader_state=loaderPos::retracted;
	else loader_state=loaderPos::extended;
	setLoader(loader_state);
}
void Shooter::Periodic(){
	if(DEBUG_REQUIREMENTS && GetCurrentCommand()!=currentOwner){
		currentOwner=GetCurrentCommand();
		std::cout << "Ownership of Shooter switched to " << currentOwner->GetName() << std::endl;
	}
}