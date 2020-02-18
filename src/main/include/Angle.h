
#ifndef ANGLE_H_
#define ANGLE_H_
#include "math.h"
#include <type_traits>

struct Radian;
struct Degree;
struct Radian{
	double value;
	Radian(double);
	Radian(Degree);
	Radian();
	Radian operator +(const Radian) const;
	Radian operator +(const Degree) const;
	Radian operator -(const Radian) const;
	Radian operator -(const Degree) const;
	template<class T>
	Radian operator *(const T) const;
	template<class T>
	Radian operator /(const T) const;
	operator double() const;
};
struct Degree{
	double value;
	Degree(double);
	Degree(Radian);
	Degree();
	Degree operator +(const Radian) const;
	Degree operator +(const Degree) const;
	Degree operator -(const Radian) const;
	Degree operator -(const Degree) const;
	template<class T>
	Degree operator *(const T) const;
	template<class T>
	Degree operator /(const T) const;
	operator double() const;
};

template<class T> Radian Radian::operator *(const T multer) const {
	static_assert(std::is_arithmetic<T>::value ,"Multiplication must be done with arithmetic type.");
    return Radian(this->value * multer);
}
template<class T> Radian Radian::operator /(const T multer) const {
	static_assert(std::is_arithmetic<T>::value ,"Division must be done with arithmetic type.");
    return Radian(this->value / multer);
}

template<class T> Degree Degree::operator *(const T multer) const {
	static_assert(std::is_arithmetic<T>::value ,"Multiplication must be done with arithmetic type.");
    return Degree(this->value * multer);
}
template<class T> Degree Degree::operator /(const T multer) const {
	static_assert(std::is_arithmetic<T>::value ,"Division must be done with arithmetic type.");
    return Degree(this->value / multer);
}


#endif /* ANGLE_H_ */
