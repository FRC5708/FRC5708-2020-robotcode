#include "commands/TurnToAngle.h"
#include "Robot.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>
#include <frc/controller/PIDController.h>
#include <functional>
#include <frc2/command/CommandScheduler.h>

TurnToAngle::TurnToAngle(Drivetrain* drivetrain, units::degree_t targetRotation) : 
	PIDCommand(
		frc2::PIDController(0.05, 0.001, 0.0), 
		[drivetrain](){ return drivetrain->GetGyroAngle(); },
		[this](){return this->targetRotation.value(); },
		[drivetrain](double d){ drivetrain->DrivePolar(0, d);},
		drivetrain),
	
	drivetrain(drivetrain),
	targetRotation(targetRotation) {
		
	// Set the controller to be continuous (because it is an angle controller)
	m_controller.EnableContinuousInput(-180, 180);	
	// Get within one degree
	GetController().SetTolerance(1);
}

TurnToAngle::TurnToAngle(TurnToAngle& otherMe) 
: TurnToAngle(otherMe.drivetrain, otherMe.targetRotation) {
	
}

bool TurnToAngle::IsFinished() { return GetController().AtSetpoint(); }

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
