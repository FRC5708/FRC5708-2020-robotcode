#include "commands/DriveToPoint.h"
#include "Robot.h"
#include <cmath>

using namespace units;

DriveToPoint::DriveToPoint(frc::Translation2d targetPoint, bool stopAfter, bool backwards) : 
targetPoint(targetPoint), stopAfter(stopAfter), backwards(backwards) {   
    // I'm too lazy to do dependency injection
    drivetrain = &Robot::GetRobot()->drivetrain;
    odometry = &Robot::GetRobot()->odometry;
    
    AddRequirements(drivetrain); 
}

void DriveToPoint::Initialize() {
    startingPoint = odometry->currentPos.Translation();
    
    std::cout << "starting driveToPoint to X:" << targetPoint.X() << " Y:" << targetPoint.Y() << std::endl;
}

constexpr double TOP_POWER = 0.4,
MIN_POWER = 0.3,
maxCentripetal = 3; // m/s^2

// https://stackoverflow.com/a/11498248/4062079

void DriveToPoint::Execute() {
    
    // Degree difference -> turning power ratio
    constexpr double kTurning = 0.1,
    // This is multiplied by the m/s^2 of centripetal acceleration over the limit, then fed into some s**t-f**kery
	 kTurnReduction = 2,
     // Motor power per meter of distance away from target
	 kForwardPower = 2;
     
    // Get absolute angle from robot's position to target's position TODO: make sure this actually works
    degree_t absAngleToTarget = units::math::atan2(targetPoint.Y() - odometry->getRoboty(), targetPoint.X() - odometry->getRobotx());
    
    // Get reletive angle from front of robot to target
    degree_t angleToTarget = absAngleToTarget - degree_t(drivetrain->GetGyroAngle());
    if (backwards) angleToTarget += degree_t(180);
    
    // Convert to 180 - -179
    angleToTarget = units::math::fmod(angleToTarget + degree_t(180.0), degree_t(360));
    if (angleToTarget < degree_t(0))
        angleToTarget += degree_t(360);
    angleToTarget = angleToTarget - degree_t(180);
        
        
    // Get rate of turning, depending on angle to target
    double turnPower = angleToTarget.value() * kTurning;
    
    // Don't turn too much
    // It's awful, but it worked OK last year so I'm putting it in here this year.
    double currentSpeed = (drivetrain->leftEncoder->GetRate() + drivetrain->rightEncoder->GetRate()) / 2.0;
    double currentCentripetal = fabs(drivetrain->gyro->GetRate() * currentSpeed);
	if (currentCentripetal > maxCentripetal) {
		turnPower /= pow(2, (currentCentripetal - maxCentripetal) * kTurnReduction);
	}
    
    double forwardPower = TOP_POWER;
    if (stopAfter) {
        forwardPower = std::max(MIN_POWER,
         std::min(TOP_POWER, kForwardPower * odometry->currentPos.Translation().Distance(targetPoint).value()));
    }
    
    if (backwards) forwardPower = -forwardPower;
    drivetrain->DrivePolar(forwardPower, turnPower);
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

void DriveToPoint::End(bool interrupted) {
    std::cout << "Ended drivetopoint" << std::endl;
}