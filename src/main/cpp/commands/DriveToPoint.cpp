#include "commands/DriveToPoint.h"
#include "Robot.h"
#include <cmath>

using namespace units;

DriveToPoint::DriveToPoint(frc::Translation2d targetPoint, bool stopAfter) : 
targetPoint(targetPoint) {   
    // I'm too lazy to do dependency injection
    drivetrain = &Robot::GetRobot()->drivetrain;
    odometry = &Robot::GetRobot()->odometry;
    
    AddRequirements(drivetrain); 
}

void DriveToPoint::Initialize() {
    
}

constexpr double TOP_POWER = 1,
MIN_POWER = 0.3,
maxCentripetal = 3; // m/s^2

void DriveToPoint::Execute() {
    
    // Degree difference -> turning power ratio
    constexpr double kTurning = 0.1,
    // This is multiplied by the m/s^2 of centripetal acceleration over the limit, then fed into some s**t-f**kery
	 kTurnReduction = 2,
     // Motor power per meter of distance away from target
	 kForwardPower = 2;
     
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

void DriveToPoint::End() {

}