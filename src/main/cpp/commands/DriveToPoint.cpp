#include "commands/DriveToPoint.h"
#include <cmath>

#define PI 3.1415926

DriveToPoint::DriveToPoint() {    
}

void DriveToPoint::Initialize() {
    // TODO: Get position from Odometry
    // For now, these magic numbers will do fine
    // Make sure that the angles are 0-360 not -180 to 180
    DriveToPoint::position = {0,0};
    DriveToPoint::heading = 0;

    // TODO: Get the destinaton point from wherever (subject to revison)
    DriveToPoint::destination = {5,5};
}

void DriveToPoint::Execute() {
    DriveToPoint::position = {0,0}; // TODO: update position and heading from odometry
    DriveToPoint::heading = 0;
    // Degree difference -> turning power ratio
    double kTurning = 0.1;
    // Get absolute angle from robot's position to target's position TODO: make sure this actually works
    float absAngleToTarget = atan2((DriveToPoint::position.y-DriveToPoint::destination.y), (DriveToPoint::position.x-DriveToPoint::destination.x));
    absAngleToTarget *= 180.0 / PI;
    // Get reletive angle from front of robot to target
    float angleToTarget = absAngleToTarget - DriveToPoint::heading;
    // Convert to 180 - -179
    // reduce the angle  
    angleToTarget =  fmod(angleToTarget, 360); 

    // force it to be the positive remainder, so that 0 <= angle < 360  
    angleToTarget = fmod((angleToTarget + 360), 360);  

    // force into the minimum absolute value residue class, so that -180 < angle <= 180  
    if (angleToTarget > 180)  
        angleToTarget -= 360;
    // Get rate of turning, depending on angle to target
    float turnRate = angleToTarget * kTurning;
/*     if (angleToTarget <= 180 && angleToTarget >= 5) {
        drive.DrivePolar(1, -turnRate); // Turn left
    }
    else if (angleToTarget > 180 && angleToTarget <= 355) {
        drive.DrivePolar(1, turnRate); // Turn right
    }
    else {
        drive.Drive(1,1);
    } */
    drive.DrivePolar(1, turnRate);
}

bool DriveToPoint::IsFinished() {
    if (sqrt(pow(position.x - destination.x, 2) + pow(position.y - destination.y, 2)) < endDistance) {
        drive.Drive(0,0);
        return true;
    }
    else {
        return false;
    }

}

void DriveToPoint::End() {

}