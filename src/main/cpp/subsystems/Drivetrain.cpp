#include "subsystems/Drivetrain.h"
#include "DIOMaps.h"
#include <ctre/Phoenix.h>
#include <frc/ADXRS450_Gyro.h>
#include <commands/DriveWithJoystick.h>
#include <iostream>

using namespace units;

constexpr inch_t ROBOT_WIDTH(28);
constexpr inch_t ROBOT_LENGTH(28.25);

Drivetrain* drivetrainInstance=nullptr;

double Drivetrain::boundValue(const double value, const double bound){
	/**
	 * Bounds value to range [-bound,bound]
	 * If value is outside boundary, return appropriate boundry. Otherwise, return value.
	 */
	if(value < (-1.0 * bound)) return -1.0 * bound;
	if(value > bound) return bound;
	return value;
}



Drivetrain::Drivetrain() :
gyro(new frc::ADXRS450_Gyro()),
leftEncoder(new frc::Encoder(leftEncoderChannel[0],leftEncoderChannel[1], false)),
rightEncoder(new frc::Encoder(rightEncoderChannel[0],rightEncoderChannel[1], true)) {
	//Set encoder and spark parameters here
	if (Drivetrain::usingTalons) {
		FLMotor = new WPI_TalonSRX(frontLeftMotorChannel);
		BLMotor = new WPI_TalonSRX(backLeftMotorChannel);
		FRMotor = new WPI_TalonSRX(frontRightMotorChannel);
		BRMotor = new WPI_TalonSRX(backRightMotorChannel);
	}
	else {
		FLMotor = new WPI_VictorSPX(frontLeftMotorChannel);
		BLMotor = new WPI_VictorSPX(backLeftMotorChannel);
		FRMotor = new WPI_VictorSPX(frontRightMotorChannel);
		BRMotor = new WPI_VictorSPX(backRightMotorChannel);
	}
	// Make sure motors are in brake mode
	// Note: BaseMotorController is applicable to all CTRE CAN motor controllers
	dynamic_cast<BaseMotorController *>(FLMotor)->SetNeutralMode(Brake);
	dynamic_cast<BaseMotorController *>(BLMotor)->SetNeutralMode(Brake);
	dynamic_cast<BaseMotorController *>(FRMotor)->SetNeutralMode(Brake);
	dynamic_cast<BaseMotorController *>(BRMotor)->SetNeutralMode(Brake);
	
	SetDefaultCommand(DriveWithJoystick::DoDrivetrain(this));
	
	constexpr double metersPerPulse = units::meter_t(units::inch_t(6.0)).value() * M_PI / 360.0;
	leftEncoder->SetDistancePerPulse(metersPerPulse);
	rightEncoder->SetDistancePerPulse(metersPerPulse);
	assert(drivetrainInstance==nullptr); //We should only have one shooter.
	drivetrainInstance=this;
}
Drivetrain* Drivetrain::getDrivetrain(){
	assert(drivetrainInstance!=nullptr);
	return drivetrainInstance;
}

void Drivetrain::Drive(const double left,const double right){
	//std::cout << "Drive with left:" << left << " right:" << right << std::endl;
	
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

void Drivetrain::checkEncoders() {
	if (!leftEncoderGood) leftEncoderGood = fabs(leftEncoder->GetDistance()) > 0.1;
	if (!rightEncoderGood) rightEncoderGood = fabs(rightEncoder->GetDistance()) > 0.1;
}
std::pair<units::meter_t, units::meter_t> Drivetrain::GetEncoderDistances() {
	checkEncoders();
	meter_t leftDistance(leftEncoder->GetDistance());
	meter_t rightDistance(rightEncoder->GetDistance());
	
	if (!leftEncoderGood && rightEncoderGood) {
		// emulate with gyro
		return { rightDistance - radian_t(degree_t(GetGyroAngle())).value() * ROBOT_WIDTH, rightDistance };
	}
	else if (!rightEncoderGood && leftEncoderGood) {
		return { leftDistance, leftDistance + radian_t(degree_t(GetGyroAngle())).value() * ROBOT_WIDTH };
	}
	else {
		// both encoders, yay!
		// or maybe no encoders
		return {leftDistance, rightDistance};
	}
}

/* std::vector<double> Drivetrain::getMotorPowers()
** Returns a vector with the current motor powers of drivetrain in the following order: Front-Left, Front-Right, Back-Left, Back-Right
*/
std::vector<double> Drivetrain::getMotorPowers(){
	std::vector<double> vect {FLMotor->Get(),FRMotor->Get(),BLMotor->Get(),BRMotor->Get()};
	return vect;
}