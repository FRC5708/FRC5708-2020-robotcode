#include "subsystems/Intake.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h> //Let's avoid the header apocalypse.
#include <iostream>

Intake intakeInstance;

Intake::Intake() :
    intakeMotor(new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(IntakeMotorChannel)),
    magazineMotor(new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(MagazineMotorChannel)) {
    
    SetDefaultCommand(DriveWithJoystick::DoIntake(this));
    
    magazineMotor->SetInverted(true);
    assert(this == &intakeInstance); // there should only be one instance.
    if(DEBUG_CONSTRUCTORS) std::cout << "Intake initialized." << std::endl;
}
Intake* Intake::getIntake(){
    return &intakeInstance;
}
void Intake::setIntake(intake_mode mode){
    this->mode=mode;
}  
void Intake::Periodic(){
    trackPressState();
    //TODO: Make ball count reset back to zero!
    switch(mode){
        case intake_mode::intake:
            intakeMotor->Set(1);
            switch(state){
                case none:
                case pressing:
                    //The ball isn't in position yet, if it even exists.
                    magazineMotor->Set(1);
                    if(DEBUG_INTAKE_MAGAZINE) std::cout << "Magazine running (ball not in magazine hold)" << std::endl;
                    break;
                case hasBall:
                case releasing:
                    if(ramp_ball_counter < RAMP_MAX_CAPACITY){
                        //We have room for more.
                        magazineMotor->Set(1); 
                        if(DEBUG_INTAKE_MAGAZINE) std::cout << "Magazine running (under ramp capacity)" << std::endl;
                        break;
                    }
                    magazineMotor->Set(0); //We're at capacity. Hold the ball.
                    if(DEBUG_INTAKE_MAGAZINE) std::cout << "Magazine stopped (at capacity and ball in magazine hold)" << std::endl;
                    break;
            }
            break;
        case intake_mode::off:
            intakeMotor->Set(0);
            magazineMotor->Set(0);
            break;
        case intake_mode::reverse:
            intakeMotor->Set(-1);
            magazineMotor->Set(-1);
            break;
        case intake_mode::force_intake:
            //Force the intake motors. Possibly ill-advised.
            intakeMotor->Set(1);
            magazineMotor->Set(1);
            if(DEBUG_INTAKE_MAGAZINE && (state==hasBall || state==releasing)) std::cout << "Magazine running (at max capacity, but forced!)" << std::endl;
            break;
    }
}
//Step the FSM that tracks the state of our intake. Note: this is *completely* independent of motor control.
void Intake::trackPressState(){
    switch(state){
        case intake_state::none: //Nothing's currently going on.
            if(intakeLimitSwitch->Get()){
                state=pressing; //Something's activated the limit switch.
                if(DEBUG_INTAKE_FSM) std::cout << "Intake FSM changed state to pressing." << std::endl;
                press_start=timing_clock.now();
            }
            break;
        case intake_state::pressing: //Something's pressing the limit switch
            if(!intakeLimitSwitch->Get()){
                //It's not pressing it anymore. 
                if(DEBUG_INTAKE_FSM) std::cout << "Intake FSM changed state to none." << std::endl;
                state=none;
                break;
            }
            if(timing_clock.now()-press_start > PRESS_TIME){
                //We've had it pressed enough.
                if(DEBUG_INTAKE_FSM) std::cout << "Intake FSM changed state to hasBall." << std::endl;
                state=hasBall;
            }
            break;
        case intake_state::hasBall: //We currently have a ball in.
            if(!intakeLimitSwitch->Get()){
                state=releasing; //We aren't actively pressing the limit switch.
                if(DEBUG_INTAKE_FSM) std::cout << "Intake FSM changed state to releasing." << std::endl;
                release_start=timing_clock.now();
            }
            break;
        case intake_state::releasing: //Nothing's pressing the limit switch, but we had a ball
            if(intakeLimitSwitch->Get()){
                //False alarm. We still have the ball.
                state=hasBall;
                if(DEBUG_INTAKE_FSM) std::cout << "Intake FSM changed state to hasBall." << std::endl;
                break;
            }
            if(timing_clock.now()-release_start > RELEASE_TIME){
                //We definitely don't have it any more. 
                state=none;
                if(DEBUG_INTAKE_FSM) std::cout << "Intake FSM changed state to none." << std::endl;
                ramp_ball_counter+=1; //Add a ball to the counter.
                if(DEBUG_INTAKE_BALL_COUNT) std::cout << "Ramp ball count " << ramp_ball_counter << std::endl;
            }
            break;
    }
}
void Intake::resetBallCounter(){
        if(DEBUG_INTAKE_BALL_COUNT) std::cout << "Reset ramp ball count." << std::endl;
        ramp_ball_counter=0;
    }
unsigned short Intake::getBallCount(){
    //TODO: IMPLEMENT ME!
    return 0;
}