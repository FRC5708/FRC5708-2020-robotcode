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

    // Get the destinaton point from whatever (subject to revison)
    DriveToPoint::destination = {5,5};
}

void DriveToPoint::Execute() {
    DriveToPoint::position = {0,0}; // TODO: update position and heading from odometry
    DriveToPoint::heading = 0;
    // Get absolute angle from robot's position to target' position
    float absAngleToTarget = atan2((DriveToPoint::position.y-DriveToPoint::destination.y), (DriveToPoint::position.x-DriveToPoint::destination.x));
    absAngleToTarget *= 180.0 / PI;
    // Get reletive angle from front of robot to target (0-360, 0 forward)
    float angleToTarget = absAngleToTarget - DriveToPoint::heading;
    // Get reletive angle from front of robot to target (180 to -180, 0 forward)
    float angleToTarget2;
    if (angleToTarget > 180){
        angleToTarget2 = (angleToTarget-180)*-1;
    }
    else {
        angleToTarget2 = angleToTarget;
    }
    // Get rate of turning, depending on angle to target
    float turnRate = sqrt(fabs(angleToTarget2))/sqrt(180);
    if (angleToTarget <= 180 && angleToTarget >= 5) {
        drive.DrivePolar(1, -turnRate); // Turn left
    }
    else if (angleToTarget > 180 && angleToTarget <= 355) {
        drive.DrivePolar(1, turnRate); // Turn right
    }
    else {
        drive.Drive(1,1);
    }
}

bool DriveToPoint::IsFinished() {
    // TODO: Convert hitbox to hitcircle
    if (fabs(position.x - destination.x) < endDistance && fabs(position.y - destination.y) < endDistance) {
        drive.Drive(0,0);
        return true;
    }
    else {
        return false;
    }

}

void DriveToPoint::End() {

}