/*Declares what ports every electronic component is attached to. 
 **The purpose of this is to avoid having "magic numbers" floating about in the code, and to make quickly changing
 **what ports a component is plugged into easy. 
 **If you are declaring an electronic component anywhere in the code, and are giving it a DIO port, you ~must~
 **do so within this header file.
*/
#pragma once

constexpr int const leftEncoderChannel[2] = {0,1}; //DIO
constexpr int const rightEncoderChannel[2] = {2,3}; //DIO

constexpr int const frontLeftMotorChannel = 3; //CAN
constexpr int const frontRightMotorChannel = 1; //CAN
constexpr int const backLeftMotorChannel = 4; //CAN
constexpr int const backRightMotorChannel = 2; //CAN

constexpr int const RightShooterMotorChannel = 0; //CAN
constexpr int const LeftShooterMotorChannel = 6; //CAN
constexpr int const ShooterCAMChannel = 10; //CAN
constexpr int const IntakeMotorChannel = 7; //CAN
constexpr int const MagazineMotorChannel = 5; //CAN

constexpr int const IntakeLimitSwitchChannel = 4; //DIO 