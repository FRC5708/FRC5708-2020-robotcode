#pragma once

constexpr bool const DEBUG_DRIVETRAIN=false; //Spam the console with Drive values. Not usually recommended.
constexpr bool const DEBUG_INTAKE_FSM=true; //Debug the intake FSM. Only logs upon state change.
constexpr bool const DEBUG_INTAKE_MAGAZINE=false; //Debug intake magazine state. Spammy.
constexpr bool const DEBUG_INTAKE_BALL_COUNT=true; //Log messages whenever a ball is intaked into the ramp, or the counter is reset.
constexpr bool const DEBUG_ODOMETRY=false; //Spam the console with odometry data. Not usually recommended.
constexpr bool const DEBUG_COMMAND_STATE=true; //Log command state changes.
constexpr bool const DEBUG_CONSTRUCTORS=false; //Log messages after subsystems succesfully instantiate. Hopefully we won't need to use this.