#include "subsystems/Drivetrain.h"

double boundValue(const double value, const double bound){
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
	FRMotor->Set(bounded_right);
	BRMotor->Set(bounded_right);
}