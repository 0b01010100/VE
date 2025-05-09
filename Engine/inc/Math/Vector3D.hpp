#pragma once
#include <math.h>

class Vector3D
{
public:
	Vector3D():x(0),y(0),z(0)
	{
	}
	Vector3D(float x,float y, float z) :x(x), y(y), z(z)
	{
	}
	Vector3D(const Vector3D& vector) :x(vector.x), y(vector.y), z(vector.z)
	{
	}

	static Vector3D lerp(const Vector3D& start, const Vector3D& end, float delta)
	{
		Vector3D v;
		v.x = start.x*(1.0f - delta) + end.x*(delta);
		v.y = start.y*(1.0f - delta) + end.y*(delta);
		v.z = start.z*(1.0f - delta) + end.z*(delta);
		return v;
	}

	Vector3D operator *(const float num) const
	{
		return Vector3D(x * num, y * num, z * num);
	}

	Vector3D operator +(const Vector3D& vec) const
	{
		return Vector3D(x + vec.x, y + vec.y, z + vec.z);
	}
	Vector3D operator -(const Vector3D& vec) const
	{
		return Vector3D(x - vec.x, y - vec.y, z - vec.z);
	}
	Vector3D operator *(const Vector3D& vec) const
	{
		return Vector3D(x * vec.x, y * vec.y, z * vec.z);
	}

	// Calculate dot product with another vector
	float dot(const Vector3D& vec) const
	{
		return x * vec.x + y * vec.y + z * vec.z;
	}

	// Normalize this vector and return the result
	Vector3D normalize() const
	{
		float len = sqrt(x * x + y * y + z * z);
		if (len < 1e-6f) return Vector3D(0, 0, 0); // Avoid division by zero
		
		float invLen = 1.0f / len;
		return Vector3D(x * invLen, y * invLen, z * invLen);
	}

	// Returns the length/magnitude of this vector
	float length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	// Returns the squared length/magnitude of this vector
	// This is faster when you just need to compare lengths
	float lengthSquared() const
	{
		return x * x + y * y + z * z;
	}
	
	// Cross product as an instance method
	Vector3D cross(const Vector3D& vec) const
	{
		return Vector3D(
			(y * vec.z) - (z * vec.y),
			(z * vec.x) - (x * vec.z),
			(x * vec.y) - (y * vec.x)
		);
	}

	~Vector3D()
	{
	}

public:
	float x, y, z;
};