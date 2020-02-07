#include "subsystems/Manipulators.h"

Manipulators::Manipulators() {
}

void Manipulators::SetShooterWheels(int power) {
    SRMotor->Set(power);
    SLMotor->Set(power);
}

void Manipulators::SetShooterCAM(int power) {
    SCMotor->Set(power);
}

void Manipulators::SetIntakeWheels(int power) {
    IMotor->Set(power);
}
