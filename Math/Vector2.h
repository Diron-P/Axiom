#ifndef VECTOR2_H
#define VECTOR2_H

#include <math.h>

namespace Axiom 
{
	namespace Math 
	{
		class Vector2 
		{
		public:
			float x;
			float y;

			Vector2()
				: x(0.0f)
				, y(0.0f)
			{
			}

			Vector2(const float& x, const float& y)
				: x(x)
				, y(y)
			{
			}

			Vector2& operator+=(const Vector2& v)
			{
				x += v.x;
				y += v.y;
				return *this;
			}

			Vector2& operator-=(const Vector2& v)
			{
				x -= v.x;
				y -= v.y;
				return *this;
			}

			Vector2& operator*=(const Vector2& v)
			{
				x *= v.x;
				y *= v.y;
				return *this;
			}

			Vector2& operator/=(const Vector2& v)
			{
				x /= v.x;
				y /= v.y;
				return *this;
			}

			Vector2 operator+(const Vector2& v) const
			{
				return Vector2(x + v.x, y + v.y);
			}

			Vector2 operator-(const Vector2& v) const
			{
				return Vector2(x - v.x, y - v.y);
			}

			float operator*(const Vector2& v) const
			{
				return (x * v.x) + (y * v.y);
			}

			Vector2 operator*(const float scalar) const
			{
				return Vector2(scalar * x, scalar * y);
			}

			Vector2 operator/(const float s) const
			{
				return Vector2(x / s, y / s);
			}

			bool operator==(const Vector2& v) const
			{
				return (x == v.x && y == v.y);
			}

			bool operator!=(const Vector2& v) const
			{
				return (x != v.x || y != v.y);
			}

			void Set(const float inX, const float inY)
			{
				x = inX;
				y = inY;
			}

			float Magnitude() const
			{
				return sqrtf((x * x) + (y * y));
			}

			float DotProduct(const Vector2& v1, const Vector2& v2)
			{
				return v1 * v2;
			}

			Vector2 Normalize(Vector2& v)
			{
				return (v / v.Magnitude());
			}
		};
	}
}

#endif
