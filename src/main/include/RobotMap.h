/*Declares what ports every electronic component is attached to. 
 **The purpose of this is to avoid having "magic numbers" floating about in the code, and to make quickly changing
 **what ports a component is plugged into easy. 
 **If you are declaring an electronic component anywhere in the code, and are giving it a DIO port, you ~must~
 **do so within this header file.
*/


constexpr int leftEncoderChannel[2] = {0,0};
constexpr int rightEncoderChannel[2] = {0,0};
constexpr int frontLeftMotorChannel = 0;
constexpr int frontRightMotorChannel = 0;
constexpr int backLeftMotorChannel = 0;
constexpr int backRightMotorChannel = 0;
constexpr int I2CPORT = 0; //CHANGE ME!
constexpr bool ENABLE_COLOR_VISION_LOGGING = true;