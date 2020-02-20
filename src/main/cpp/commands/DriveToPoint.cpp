#include "commands/DriveToPoint.h"
#include <cmath>

using namespace units;

DriveToPoint::DriveToPoint() {    
}

void DriveToPoint::Initialize() {
    
}

constexpr double TOP_POWER = 1;

void DriveToPoint::Execute() {
    
    
    // Degree difference -> turning power ratio
    double kTurning = 0.1;
    // Get absolute angle from robot's position to target's position TODO: make sure this actually works
    degree_t absAngleToTarget = degree_t(360) - units::math::atan2(targetPoint.X() - odometry->getRobotx(), targetPoint.Y() - odometry->getRoboty());
    
    // Get reletive angle from front of robot to target
    degree_t angleToTarget = absAngleToTarget - degree_t(drivetrain->GetGyroAngle());
    
    // Convert to 180 - -179
    // reduce the angle  
    angleToTarget =  units::math::fmod(angleToTarget, degree_t(360)); 
    // force it to be the positive remainder, so that 0 <= angle < 360  
    angleToTarget = units::math::fmod((angleToTarget + degree_t(360)), degree_t(360));  
    // force into the minimum absolute value residue class, so that -180 < angle <= 180  
    if (angleToTarget > degree_t(180)) angleToTarget -= degree_t(360);
        
        
    // Get rate of turning, depending on angle to target
    float turnRate = angleToTarget.value() * kTurning;
    
    drivetrain->DrivePolar(TOP_POWER, turnRate);
}

bool DriveToPoint::IsFinished() {
    if (odometry->currentPos.Translation().Distance(targetPoint) < endDistance
    || odometry->currentPos.Translation().Distance(startingPoint) > targetPoint.Distance(startingPoint)) {
        drivetrain->Drive(0,0);
        return true;
    }
    else {
        return false;
    }

}

void DriveToPoint::End() {

}