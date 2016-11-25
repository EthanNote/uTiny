#pragma once
#include<ostream>

#ifndef UTINY_API

#define UTINY_API __declspec(dllimport)

#endif

class UTINY_API Vector3
{
public:
	Vector3(float x = 0, float y = 0, float z = 0);
	~Vector3();

	float x, y, z;

	Vector3 operator +(const Vector3& vec) const;
	Vector3 operator -(const Vector3& vec) const;
	float operator*(const Vector3& vec) const;
	Vector3 operator^(const Vector3& vec) const;
	Vector3 operator*(float f) const;
	Vector3 operator/(float d) const;
	float Length2() const;
	float Length() const;
	Vector3 Normal() const;
	void Normalize();

	friend std::ostream& operator<<(std::ostream &stream, Vector3& v);

	static Vector3 Zero();
	static Vector3 One();
	static Vector3 Forward();
	static Vector3 Backward();
	static Vector3 Left();
	static Vector3 Right();
	static Vector3 Up();
	static Vector3 Down();

};

