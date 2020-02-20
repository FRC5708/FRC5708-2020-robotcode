#include "commands/VisionDrive.h"
#include "Robot.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>
#include <frc/controller/PIDController.h>
#include <functional>
#include <frc2/command/CommandScheduler.h>

VisionDrive::VisionDrive() : PIDCommand(
    frc2::PIDController(0.05, 0.001, 0.0), 
    [this](){return this->currentRotation;},
    [this](){return this->targetRotation;},
    [=](double d){Robot::GetRobot()->drivetrain.DrivePolar(0, d);}
){
    AddRequirements({&Robot::GetRobot()->drivetrain});
    GetController().SetTolerance(1);
}

void VisionDrive::Initialize(){

    currentRotation = 0.0;
    targetRotation = 0.0;

    currentTarget = Robot::GetRobot()->visionReceiver.getBestTarget();
    if(currentTarget.hasTarget){
        targetRotation = currentTarget.target.robotAngle.value();
    }
}

void VisionDrive::Execute(){
    //set current and target rotations in here and they will automatically be
    //tracked by the PIDCommand

    //get the most up to date vision data
    if(Robot::GetRobot()->visionReceiver.newData){
        currentTarget = Robot::GetRobot()->visionReceiver.getBestTarget();
    }
    if(currentTarget.hasTarget){
        targetRotation = currentTarget.target.robotAngle.value();
    }
}

void VisionDrive::End(bool interrupted){
    targetRotation = 0;
}
