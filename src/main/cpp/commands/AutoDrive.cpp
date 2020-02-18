#include "commands/AutoDrive.h"
#include "Robot.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <array>
#include <frc/controller/PIDController.h>
#include <functional>
#include <frc2/command/CommandScheduler.h>

AutoDrive::AutoDrive()
 : PIDCommand(frc2::PIDController(0.05, 0.001, 0.0), 
    [this](){return this->currentRotation;},
    [this](){return this->targetRotation;},
    [=](double d){Robot::GetRobot()->drivetrain.DrivePolar(0, d);}) {

    GetController().SetTolerance(1);
}

void AutoDrive::Initialize(){

    currentRotation = 0.0;
    targetRotation = 0.0;

    currentTarget = Robot::GetRobot()->visionReceiver.getBestTarget();
    if(currentTarget.hasTarget){
        targetRotation = currentTarget.target.robotAngle.value();
    }
}

void AutoDrive::Execute(){
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

void AutoDrive::End(bool interrupted){
    targetRotation = 0;
}
