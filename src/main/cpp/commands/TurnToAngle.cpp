#include "commands/TurnToAngle.h"
#include "Robot.h"

#include <iostream>
#include <frc/controller/PIDController.h>
#include <frc2/command/CommandScheduler.h>

TurnToAngle::TurnToAngle(Drivetrain* drivetrain, units::degree_t targetRotation) : 
	PIDCommand(
		frc2::PIDController(0.05, 0.005, 0.005), 
		[drivetrain](){ return drivetrain->GetGyroAngle(); },
		[this](){return this->targetRotation.value(); },
		[drivetrain](double d){ 
			//std::cout << "turn power: " << d << std::endl;
			drivetrain->DrivePolar(0, std::copysign(std::max(fabs(d), 0.07), d));
			//drivetrain->DrivePolar(0, d);
			},
		drivetrain),
	
	drivetrain(drivetrain),
	targetRotation(targetRotation) {
		
	AddRequirements(drivetrain);
		
	// Set the controller to be continuous (because it is an angle controller)
	m_controller.EnableContinuousInput(-180, 180);	
	// Get within one degree
	GetController().SetTolerance(3, 50);
}

TurnToAngle::TurnToAngle(const TurnToAngle& otherMe) 
: TurnToAngle(otherMe.drivetrain, otherMe.targetRotation) {
	
}

void TurnToAngle::End(bool interrupted) {
	drivetrain->Drive(0, 0);
	std::cout << "Ending turntoangle" << std::endl;
}

bool TurnToAngle::IsFinished() { return GetController().AtSetpoint(); }


TurnToPoint::TurnToPoint(frc::Translation2d point, bool backwards) : 
TurnToAngle(&Robot::GetRobot()->drivetrain, units::degree_t(0)), targetPoint(point), backwards(backwards) {
	
}
void TurnToPoint::Initialize() {
	
	frc::Translation2d here = Robot::GetRobot()->odometry.currentPos.Translation();
	targetRotation = units::math::atan2(targetPoint.Y() - here.Y(), targetPoint.X() - here.X());
	if (backwards) targetRotation -= units::degree_t(180);
	
	
	std::cout << "starting turntopoint to " << targetRotation << std::endl;
}

VisionDrive::VisionDrive() : TurnToAngle(&Robot::GetRobot()->drivetrain, units::degree_t(0)) {
	
}

void VisionDrive::Initialize(){

	currentTarget = Robot::GetRobot()->visionReceiver.getBestTarget();
	if(currentTarget.hasTarget){
		SetAngle();
	}
	else {
		Cancel();
	}
}

void VisionDrive::SetAngle() {
	targetRotation = units::degree_t(drivetrain->GetGyroAngle()) + currentTarget.target.robotAngle;
}

void VisionDrive::Execute(){
	//set current and target rotations in here and they will automatically be
	//tracked by the PIDCommand

	//get the most up to date vision data
	if(Robot::GetRobot()->visionReceiver.newData){
		currentTarget = Robot::GetRobot()->visionReceiver.getBestTarget();
	}
	if(currentTarget.hasTarget){
		SetAngle();
	}
}

void VisionDrive::End(bool interrupted){
	
}
