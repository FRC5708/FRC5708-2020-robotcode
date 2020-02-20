#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/PIDCommand.h>


#include "subsystems/VisionReceiver.h"
#include "commands/DriveWithJoystick.h"

class VisionDrive : public frc2::PIDCommand,DriveWithJoystick::InterruptableByController{
private:
    VisionReceiver::PossibleTarget currentTarget;
public:

    struct Point {
        double x, y;
    };

    double targetRotation = 0.0;
    double currentRotation = 0.0;

    VisionDrive();
    void Initialize() override;
	void Execute() override;
    void End(bool interrupted) override;
};