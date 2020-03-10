#include "commands/TurnToAngle.h"

#include <iostream>
#include <frc/controller/PIDController.h>
#include <frc2/command/CommandScheduler.h>
#include "subsystems/Drivetrain.h"
#include "subsystems/Odometry.h"

TurnToAngle::TurnToAngle(units::degree_t targetRotation) : 
	PIDCommand(
		frc2::PIDController(0.05, 0.005, 0.005), 
		[this](){ return Odometry::getOdometry()->GetGyroAngle(); },
		[this](){return this->targetRotation.value(); },
		[this](double d){ 
			//std::cout << "turn power: " << d << std::endl;
			Drivetrain::getDrivetrain()->DrivePolar(0, std::copysign(std::max(fabs(d), 0.07), d));
			//drivetrain->DrivePolar(0, d);
			},
		Drivetrain::getDrivetrain()),
		targetRotation(targetRotation)
	{
		
	AddRequirements(Drivetrain::getDrivetrain());
		
	// Set the controller to be continuous (because it is an angle controller)
	m_controller.EnableContinuousInput(-180, 180);	
	// Get within one degree
	GetController().SetTolerance(3, 50);
}

TurnToAngle::TurnToAngle(const TurnToAngle& otherMe) 
: TurnToAngle(otherMe.targetRotation) {
	
}

void TurnToAngle::End(bool interrupted) {
	Drivetrain::getDrivetrain()->Drive(0, 0);
	std::cout << "Ending turntoangle" << std::endl;
}

bool TurnToAngle::IsFinished() { return GetController().AtSetpoint(); }


TurnToPoint::TurnToPoint(frc::Translation2d point, bool backwards) : 
TurnToAngle(units::degree_t(0)), targetPoint(point), backwards(backwards) {
	
}
void TurnToPoint::Initialize() {
	
	frc::Translation2d here = Odometry::getOdometry()->currentPos.Translation();
	targetRotation = units::math::atan2(targetPoint.Y() - here.Y(), targetPoint.X() - here.X());
	if (backwards) targetRotation -= units::degree_t(180);
	
	
	std::cout << "starting turntopoint to " << targetRotation << std::endl;
}

VisionDrive::VisionDrive() : TurnToAngle(units::degree_t(0)) {
	
}

void VisionDrive::Initialize(){

	currentTarget = VisionReceiver::getVisionReceiver()->getBestTarget();
	if(currentTarget.hasTarget){
		SetAngle();
	}
	else {
		Cancel();
	}
}

void VisionDrive::SetAngle() {
	targetRotation = units::degree_t(Odometry::getOdometry()->GetGyroAngle()) + currentTarget.target.robotAngle;
}

void VisionDrive::Execute(){
	//set current and target rotations in here and they will automatically be
	//tracked by the PIDCommand

	//get the most up to date vision data
	if(VisionReceiver::getVisionReceiver()->newData){
		currentTarget = VisionReceiver::getVisionReceiver()->getBestTarget();
	}
	if(currentTarget.hasTarget){
		SetAngle();
	}
}