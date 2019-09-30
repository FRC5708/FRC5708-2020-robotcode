/*Declares what ports every electronic component is attached to. 
 **The purpose of this is to avoid having "magic numbers" floating about in the code, and to make quickly changing
 **what ports a component is plugged into easy. 
 **If you are declaring an electronic component anywhere in the code, and are giving it a DIO port, you ~must~
 **do so within this header file.
*/


constexpr int const leftEncoderChannel[2] = {0,0};
constexpr int const rightEncoderChannel[2] = {0,0};
constexpr int const frontLeftMotorChannel = 0;
constexpr int const frontRightMotorChannel = 0;
constexpr int const backLeftMotorChannel = 0;
constexpr int const backRightMotorChannel = 0;