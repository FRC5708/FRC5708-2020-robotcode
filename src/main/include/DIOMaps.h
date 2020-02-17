/*Declares what ports every electronic component is attached to. 
 **The purpose of this is to avoid having "magic numbers" floating about in the code, and to make quickly changing
 **what ports a component is plugged into easy. 
 **If you are declaring an electronic component anywhere in the code, and are giving it a DIO port, you ~must~
 **do so within this header file.
*/
#pragma once

constexpr int const leftEncoderChannel[2] = {0,1};
constexpr int const rightEncoderChannel[2] = {2,3};

constexpr int const frontLeftMotorChannel = 3;
constexpr int const frontRightMotorChannel = 1;
constexpr int const backLeftMotorChannel = 4;
constexpr int const backRightMotorChannel = 2; 

constexpr int const RightShooterMotorChannel = 0;
constexpr int const LeftShooterMotorChannel = 6;
constexpr int const ShooterCAMChannel = 10;
constexpr int const IntakeMotorChannel = 7;
constexpr int const MagazineMotorChannel = 5;
