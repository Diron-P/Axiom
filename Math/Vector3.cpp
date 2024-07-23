#include "Vector3.h"

Axiom::Math::Vector3::Vector3()
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

Axiom::Math::Vector3::Vector3(const float& x, const float& y, const float& z)
	: x(x)
	, y(y)
	, z(z)
{
}

Axiom::Math::Vector3& operator+=(Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	v.x += v1.x;
	v.y += v1.y;
	v.z += v1.z;

	return v;
}

Axiom::Math::Vector3& operator-=(Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	v.x -= v1.x;
	v.y -= v1.y;
	v.z -= v1.z;

	return v;
}

Axiom::Math::Vector3& operator*=(Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	v.x *= v1.x;
	v.y *= v1.y;
	v.z *= v1.z;

	return v;
}

Axiom::Math::Vector3& operator/=(Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	v.x /= v1.x;
	v.y /= v1.y;
	v.z /= v1.z;

	return v;
}

Axiom::Math::Vector3 operator+(const Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	return Axiom::Math::Vector3(v.x + v1.x, v.y + v1.y, v.z + v1.z);
}

Axiom::Math::Vector3 operator-(const Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	return Axiom::Math::Vector3(v.x - v1.x, v.y - v1.y, v.z - v1.z);
}

float operator*(const Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	return (v.x * v1.x) + (v.y * v1.y) + (v.z * v1.z);
}

Axiom::Math::Vector3 operator*(const Axiom::Math::Vector3& v, const float scalar)
{
	return Axiom::Math::Vector3(scalar * v.x, scalar * v.y, scalar * v.z);
}

Axiom::Math::Vector3 operator^(const Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	return Axiom::Math::Vector3(v.y * v1.z - v.z * v1.y, v.z * v1.x - v.x * v1.z, v.x * v1.y - v.y * v1.x);
}

bool operator==(const Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	return (v.x == v1.x && v.y == v1.y && v.z == v1.z);
}

bool operator!=(const Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	return (v.x != v1.x || v.y != v1.y || v.z != v1.z);
}

Axiom::Math::Vector3 operator/(const Axiom::Math::Vector3& v, const float s)
{
	return Axiom::Math::Vector3(v.x / s, v.y / s, v.z / s);
}

Axiom::Math::Vector3& Axiom::Math::Vector3::MakeZero()
{
	x = y = z = 0.0f;
	return *this;
}

float Axiom::Math::Vector3::Magnitude()
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

void Axiom::Math::Vector3::Set(float inX, float inY, float inZ)
{
	x = inX;
	y = inY;
	z = inZ;
}

/********************************************************************
// NON-MEMBER FUNCTIONS
********************************************************************/
Axiom::Math::Vector3 Normalize(Axiom::Math::Vector3& v)
{
	Axiom::Math::Vector3 result;
	float length = v.Magnitude();
	if (length > 0.0f) {
		float invLen = 1.0f / length;
		result.x = v.x * invLen;
		result.y = v.y * invLen;
		result.z = v.z * invLen;
	}

	return result;
}

float DotProduct(const Axiom::Math::Vector3& v, const Axiom::Math::Vector3& v1)
{
	return v * v1;
}

Axiom::Math::Vector3 CrossProduct(const Axiom::Math::Vector3& v1, const Axiom::Math::Vector3& v2)
{
	return v1 ^ v2;
}
