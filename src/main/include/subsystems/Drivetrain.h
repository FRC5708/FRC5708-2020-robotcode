#pragma once

#include <frc2/command/SubsystemBase.h>
#include <vector>
#include <frc/SpeedController.h>
#include <frc/Encoder.h>
#include <frc/GyroBase.h>
#include <units/units.h>

class Drivetrain : public frc2::SubsystemBase {
protected:
	const static bool usingTalons=false;
	frc::SpeedController* FLMotor;
	frc::SpeedController* FRMotor;	
	frc::SpeedController* BLMotor;
	frc::SpeedController* BRMotor;
	
	bool leftEncoderGood = false, rightEncoderGood = false;
	void checkEncoders();
public:

	Drivetrain();
	void Drive(double left, double right);
	void DrivePolar(double power, double turn);
	double boundValue(double value, double bound);
	
	// Returns counterclockwise-positive, which is the convention everywhere else in the code.
	inline double GetGyroAngle() { return -gyro->GetAngle(); };
	
    frc::Gyro* const gyro;
	frc::Encoder* const leftEncoder;
	frc::Encoder* const rightEncoder;
	std::pair<units::meter_t, units::meter_t> GetEncoderDistances();
	
	std::vector<double> getMotorPowers();
};