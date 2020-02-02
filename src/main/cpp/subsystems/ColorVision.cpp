#include "subsystems/ColorVision.h"
#include <iostream>
/*
* Documentation: http://www.revrobotics.com/content/sw/color-sensor-v3/sdk/docs/cpp/index.html
* Sample Code: https://github.com/REVrobotics/Color-Sensor-v3-Examples/blob/master/C%2B%2B/Read%20RGB%20Values/src/main/cpp/Robot.cpp
* Product Page: http://www.revrobotics.com/rev-31-1557/
* Note that building this code requires downloading the sdk at http://revrobotics.com/content/sw/color-sensor-v3/sdk/Color-Sensor-V3-SDK-v1.0.0.zip
*/
ColorVision::ColorVision(){
    //Possibly change calibration values here?
}
void ColorVision::Periodic(){
	string color1 = "";
	string color2 = "";
	string color3 = "";
	string color4 = "";
    if(ENABLE_COLOR_VISION_LOGGING){
        auto detectedColor = colorSensor.GetRawColor();
        std::cout << "Red: " << detectedColor.red << std::endl;
        std::cout << "Blue: " << detectedColor.blue << std::endl;
        std::cout << "Green: " << detectedColor.green << std::endl;
        uint32_t proximity = colorSensor.GetProximity();
        std::cout << "Proximity: " << proximity << std::endl;
		//determines whether color detected is red, blue green, and yellow
		//also sets the order detected with each new color
	if (MatchColor(detectedColor).compare("blue") == 1) {
		cout MatchColor(detectedColor);
		color4 = color3;
		color3 = color2;
		color2 = color1;
		color1 = "blue" };
	if (MatchColor(detectedColor).compare("yellow") == 1) {
		cout MatchColor(detectedColor);
		color4 = color3;
		color3 = color2;
		color2 = color1;
		color1 = "yellow"; };
	if (MatchColor(detectedColor).compare("green") == 1) {
		cout MatchColor(detectedColor);
		color4 = color3;
		color3 = color2;
		color2 = color1;
		color1 = "green"; };
	if (MatchColor(detectedColor).compare("red") == 1) {
		cout MatchColor(detectedColor);
		color4 = color3;
		color3 = color2;
		color2 = color1;
		color1 = "red"; };
	else cout "Different color";
	//determines each half rotation based on the order the colors have been detected
	double rotations = 0;
	if (color1.compare("yellow") == 1 && color2.compare("blue") == 1 && color3.compare("green") == 1 && color4.compare("red") == 1) {
		rotations = rotations + 0.5;
		cout "Rotations: " << rotations;
	}
	else cout "Rotations: " << rotations;
    }
}