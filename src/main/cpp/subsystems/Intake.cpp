#include "subsystems/Intake.h"
#include <ctre/phoenix/motorcontrol/can/WPI_TalonSRX.h> //Let's avoid the header apocalypse.

Intake::Intake() :
    intakeMotor(new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(IntakeMotorChannel)),
    magazineMotor(new ctre::phoenix::motorcontrol::can::WPI_TalonSRX(MagazineMotorChannel)) {
    
    SetDefaultCommand(DriveWithJoystick::DoIntake(this));
    
    magazineMotor->SetInverted(true);
}

void Intake::setIntake(intake_mode mode){
    this->mode=mode;
}  
void Intake::Periodic(){
    trackPressState();
    switch(mode){
        case intake_mode::intake:
            intakeMotor->Set(1);
            magazineMotor->Set(1);
            break;
        case intake_mode::off:
            intakeMotor->Set(0);
            magazineMotor->Set(0);
            break;
        case intake_mode::reverse:
            intakeMotor->Set(-1);
            magazineMotor->Set(-1);
            break;
    }
}
//Step the FSM that tracks the state of our intake. Note: this is *completely* independent of motor control.
void Intake::trackPressState(){
    if(DEBUG_INTAKE_FSM) std::cout << "Intake FSM state: " << state << std::endl; 
    switch(state){
        case intake_state::none: //Nothing's currently going on.
            if(intakeLimitSwitch->Get()){
                state=pressing; //Something's activated the limit switch.
                press_start=timing_clock.now();
            }
            break;
        case intake_state::pressing: //Something's pressing the limit switch
            if(!intakeLimitSwitch->Get()){
                //It's not pressing it anymore. 
                state=none;
                break;
            }
            if(timing_clock.now()-press_start > PRESS_TIME){
                //We've had it pressed enough.
                state=hasBall;
            }
            break;
        case intake_state::hasBall: //We currently have a ball in.
            if(!intakeLimitSwitch->Get()){
                state=releasing; //We aren't actively pressing the limit switch.
                release_start=timing_clock.now();
            }
            break;
        case intake_state::releasing: //Nothing's pressing the limit switch, but we had a ball
            if(intakeLimitSwitch->Get()){
                //False alarm. We still have the ball.
                state=hasBall;
                break;
            }
            if(timing_clock.now()-release_start > RELEASE_TIME){
                //We definitely don't have it any more. 
                state=none;
                ramp_ball_counter+=1; //Add a ball to the counter.
            }
            break;
    }
}
unsigned short Intake::getBallCount(){
    //TODO: IMPLEMENT ME!
}