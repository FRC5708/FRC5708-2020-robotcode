#include "commands/DriveToPoint.h"
#include <cmath>

#define PI 3.1415926

DriveToPoint::DriveToPoint() {    
}

void DriveToPoint::Initialize() {
    // Get position from Odometry
    // For now, these magic numbers will do fine
    // Make sure that the angles are 0-360 not -180 to 180
    DriveToPoint::position = {0,0};
    DriveToPoint::heading = 0;

    // Get the destinaton point from whatever (subject to revison)
    DriveToPoint::destination = {5,5};
}

void DriveToPoint::Execute() {
    DriveToPoint::position = {0,0};
    DriveToPoint::heading = 0;
    float absAngleToTarget = atan2((DriveToPoint::position.y-DriveToPoint::destination.y), (DriveToPoint::position.x-DriveToPoint::destination.x));
    absAngleToTarget *= 180.0 / PI;
    float angleToTarget = absAngleToTarget - DriveToPoint::heading;
    
    if (angleToTarget <= 90 && angleToTarget >= 5 || angleToTarget <= 270 && angleToTarget >= 185) {
        drive.DrivePolar(1, -1); // Turn left
    }
    else if (angleToTarget > 90 && angleToTarget <= 175 || angleToTarget > 270 && angleToTarget <= 355) {
        drive.DrivePolar(1, 1); // Turn right
    }
}

bool DriveToPoint::IsFinished() {
    return true;
}

void DriveToPoint::End() {
    
}