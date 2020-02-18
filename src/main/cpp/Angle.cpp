#include "math.h"
#include "Angle.h"

Radian::Radian(const double value){
	this->value=value;
}
Radian::Radian(const Degree value){
	this->value=value.value/360*2*M_PI;
}
Radian::Radian(){

}
Radian Radian::operator +(const Radian summer) const {
	return Radian(this->value+summer.value);
}
Radian Radian::operator +(const Degree summer) const {
	return Radian(this->value+summer.value*2* M_PI / 360.0);
}
Radian Radian::operator -(const Radian summer) const {
	return Radian(this->value-summer.value);
}
Radian Radian::operator -(const Degree summer) const {
	return Radian(this->value-summer.value*2* M_PI / 360.0);
}
Radian::operator double() const {
	return this->value;
}


Degree::Degree(const double value) {
	this->value=value;
}
Degree::Degree(const Radian value) {
	this->value=value.value*360/2/M_PI;
}
Degree::Degree(){

}
Degree Degree::operator +(const Radian summer) const {
	return Degree(this->value+summer.value*360/2/M_PI);
}
Degree Degree::operator +(const Degree summer) const {
	return Degree(this->value+summer.value);
}
Degree Degree::operator -(const Radian summer) const {
	return Degree(this->value-summer.value*360/2/M_PI);
}
Degree Degree::operator -(const Degree summer) const {
	return Degree(this->value-summer.value);
}
Degree::operator double() const {
	return this->value;
}