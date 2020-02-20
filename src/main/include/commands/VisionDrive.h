#pragma once

#include <chrono>
#include <iostream>
#include <fstream>
#include <functional>

#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>
#include <frc2/command/PIDCommand.h>


#include "subsystems/VisionReceiver.h"

class MyPIDCommand : public frc2::PIDCommand {
public:
    MyPIDCommand(std::function<double()> measure, std::function<double()> setpoint, std::function<void(double)> useOut);
    bool IsFinished() override;
};

class VisionDrive : public frc2::PIDCommand {
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