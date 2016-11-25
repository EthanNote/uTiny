#define UTINY_API __declspec(dllexport)

#include "../include/Vector3.h"
#include <math.h>

Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::~Vector3()
{
}

Vector3 Vector3::operator+(const Vector3 & vec) const
{
	return Vector3(x + vec.x, y + vec.y, z + vec.z);
}

Vector3 Vector3::operator-(const Vector3 & vec) const
{
	return Vector3(x - vec.x, y - vec.y, z - vec.z);
}

float Vector3::operator*(const Vector3 & vec) const
{
	return x * vec.x + y * vec.y + z * vec.z;
}

Vector3 Vector3::operator^(const Vector3 & vec) const
{
	return Vector3(y*vec.z-z*vec.y, z*vec.x-x*vec.z, x*vec.y-y*vec.x);
}

Vector3 Vector3::operator*(float f) const
{
	return Vector3(x*f, y*f, z*f);
}

Vector3 Vector3::operator/(float d) const
{
	return Vector3(x / d, y / d, z / d);
}

float Vector3::Length2() const
{
	return x*x + y*y + z*z;
}

float Vector3::Length() const
{
	return sqrtf(this->Length2());
}

Vector3 Vector3::Normal() const
{
	return *this / this->Length();
}

void Vector3::Normalize()
{
	*this = this->Normal();
}

Vector3 Vector3::Zero()
{
	return Vector3(0,0,0);
}

Vector3 Vector3::One()
{
	return Vector3(1,1,1);
}

Vector3 Vector3::Forward()
{
	return Vector3(0,0,-1);
}

Vector3 Vector3::Backward()
{
	return Vector3(0,0,1);
}

Vector3 Vector3::Left()
{
	return Vector3(-1,0,0);
}

Vector3 Vector3::Right()
{
	return Vector3(1,0,0);
}

Vector3 Vector3::Up()
{
	return Vector3(0,1,0);
}

Vector3 Vector3::Down()
{
	return Vector3(0,-1,0);
}

std::ostream& operator<<(std::ostream & stream, Vector3& v)
{
	return stream << "(" << v.x << "," << v.y << "," << v.z << ")";	
}
