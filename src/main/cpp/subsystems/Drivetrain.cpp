#include "subsystems/Drivetrain.h"
#include <iostream>

double Drivetrain::boundValue(const double value, const double bound){
	/**
	 * Bounds value to range [-bound,bound]
	 * If value is outside boundary, return appropriate boundry. Otherwise, return value.
	 */
	if(value < (-1.0 * bound)) return -1.0 * bound;
	if(value > bound) return bound;
	return value;
}




Drivetrain::Drivetrain() {
	//Set encoder and spark parameters here
}

void Drivetrain::Drive(const double left,const double right){
	double bounded_left=boundValue(left,1.0);
	double bounded_right=boundValue(right,1.0);
	FLMotor->Set(bounded_left);
	BLMotor->Set(bounded_left);
	FRMotor->Set(-1*bounded_right);
	BRMotor->Set(-1*bounded_right);
}
void Drivetrain::DrivePolar(const double power, const double turn){
	double bounded_power = boundValue(power, 1.0);
	double bounded_turn = boundValue(turn, 1.0);
	double v = (1-fabs(bounded_turn)) * (bounded_power) + bounded_power;
	double w = (1-fabs(bounded_power)) * (bounded_turn) + bounded_turn;
	double rightMotorOutput = (v+w)/2;
	double leftMotorOutput = (v-w)/2;

	Drive(leftMotorOutput,rightMotorOutput);
}