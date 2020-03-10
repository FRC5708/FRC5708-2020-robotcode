#include "commands/ShootCommand.h"
#include "subsystems/Intake.h"


ShootCommand::ShootCommand(double power) : shooterSpeed(power) {
	// Removed because this is always called from doShooter or ShootMultiple
	//AddRequirements({Shooter::getShooter()});
	
	AddRequirements(Intake::getIntake());
}

// TODO: test and set these values!
std::chrono::milliseconds totalShootTime{1000};
std::chrono::milliseconds pusherMoveTime{500};

void ShootCommand::Initialize() {
	shootingStarted = false;
}

void ShootCommand::Execute() {
	
	Shooter::getShooter()->setShooterWheels(shooterSpeed);
	
	if (!shootingStarted) {
		if (Shooter::getShooter()->isSpunTo(shooterSpeed)) {
			shootingStarted = true;
			shootStartTime = std::chrono::steady_clock::now();
			Shooter::getShooter()->setLoader(Shooter::loaderPos::extended);
		}
	}
	else {
		Intake::getIntake()->setIntake(Intake::intake_mode::magazineOnly);
		if (std::chrono::steady_clock::now() - shootStartTime >= pusherMoveTime) {
			Shooter::getShooter()->setLoader(Shooter::loaderPos::retracted);
		}
	}
}


bool ShootCommand::IsFinished() {
	return (std::chrono::steady_clock::now() - shootStartTime >= totalShootTime);
}
void ShootCommand::End(bool interrupted) {
	Shooter::getShooter()->setShooterWheels(0);
}

ShootMultiple::ShootMultiple(unsigned short count, double power){
	AddRequirements(Shooter::getShooter());
	for(unsigned short i=0;i<count;i++){
		AddCommands(ShootCommand(power));
	}
}