/*----------------------------------------------------------------------------*/
/* Copyright (c) 2019-2020 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
#include <frc2/command/CommandBase.h>
#include <frc2/command/CommandHelper.h>

class IntakeCommand : public frc2::CommandHelper<frc2::CommandBase, IntakeCommand> {
public:
	IntakeCommand();
	
	void Initialize() override;
	void Execute() override;
	bool IsFinished() override; 
	
private:
	std::chrono::steady_clock::time_point startTime;
};