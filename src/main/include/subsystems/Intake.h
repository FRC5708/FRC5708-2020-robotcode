#pragma once

#include <chrono>

#include <frc2/command/SubsystemBase.h>
#include <frc/SpeedController.h>
#include <frc/DigitalInput.h>

#include "commands/DriveWithJoystick.h"
#include "DIOMaps.h"
#include "DebugValues.h"

constexpr std::chrono::milliseconds const PRESS_TIME{50}; //Time (in milliseconds) the limit switch has to be held for us to think we have a ball
constexpr std::chrono::milliseconds const RELEASE_TIME{50}; //Time (in milliseconds) the limit switch has to be released for us to think that the ball has moved on.
constexpr unsigned short const START_BALL_COUNT=3; //How many balls do we preload?
constexpr unsigned short const RAMP_MAX_CAPACITY=3;

class Intake : public frc2::SubsystemBase {
public:
    enum intake_mode{intake,off,reverse,force_intake};
    enum intake_state{none,pressing,hasBall,releasing};
private:
    frc::SpeedController* const intakeMotor;
    frc::SpeedController* const magazineMotor;
    frc::DigitalInput* intakeLimitSwitch=new frc::DigitalInput(IntakeLimitSwitchChannel);

    intake_mode mode=off; 
    intake_state state=none;
    std::chrono::steady_clock timing_clock;
    std::chrono::steady_clock::time_point press_start;
    std::chrono::steady_clock::time_point release_start;

    void Periodic() override;
    void trackPressState();
    unsigned short ramp_ball_counter=START_BALL_COUNT; //How many balls are currently in the ramp
public:
	Intake();
    static Intake* getIntake(); //Get the singleton instance of the intake. 
	void setIntake(intake_mode mode);
    unsigned short getBallCount(); //TODO: IMPLEMENT ME!
    void resetBallCounter(unsigned short count=START_BALL_COUNT);
    void decrementBallCounter();
    
};