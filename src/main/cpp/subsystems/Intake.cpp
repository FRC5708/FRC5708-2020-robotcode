#include "subsystems/Intake.h"
#include <ctre/Phoenix.h>
#include "DIOMaps.h"

Intake::Intake() :
    intakeMotor(new WPI_TalonSRX(IntakeMotorChannel)),
    magazineMotor(new WPI_TalonSRX(MagazineMotorChannel)) {
    
    SetDefaultCommand(DriveWithJoystick::DoIntake(this));
    
    magazineMotor->SetInverted(true);
}

void Intake::setIntake(intake_mode mode){
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
