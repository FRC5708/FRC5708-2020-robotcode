#include "commands/ShootCommand.h"


ShootCommand::ShootCommand(double power) : shooterSpeed(power) {
	AddRequirements({Shooter::getShooter()});
	
}

// TODO: test and set these values!
std::chrono::milliseconds totalShootTime{1000};
std::chrono::milliseconds pusherMoveTime{500};

void ShootCommand::Execute() {
	
	Shooter::getShooter()->setShooterWheels(shooterSpeed);
	
	if (!shootingStarted) {
		if (Shooter::getShooter()->isSpunTo(shooterSpeed)) {
			shootingStarted = true;
			shootStartTime = std::chrono::steady_clock::now();
			Shooter::getShooter()->setLoader(Shooter::loaderPos::extended);
		}
	}
	else if (std::chrono::steady_clock::now() - shootStartTime >= pusherMoveTime) {
		Shooter::getShooter()->setLoader(Shooter::loaderPos::retracted);
	}
}


bool ShootCommand::IsFinished() {
	return (std::chrono::steady_clock::now() - shootStartTime >= totalShootTime);
}
void ShootCommand::End(bool interrupted) {
	Shooter::getShooter()->setShooterWheels(0);
}