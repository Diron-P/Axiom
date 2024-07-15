#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <math.h>

//PI defines
constexpr float PI = 3.14159265359f;
constexpr float PIDIV4 = 0.785398163f;

namespace Axiom
{
	namespace Math
	{
		//Trigonometric Functions
		inline float Sin(float value)
		{
			return sinf(value);
		}

		inline float Cos(float value)
		{
			return cosf(value);
		}

		inline float Tan(float value)
		{
			return tanf(value);
		}

		inline float ASin(float value)
		{
			return asinf(value);
		}

		inline float ACos(float value)
		{
			return acosf(value);
		}

		inline float ATan(float value)
		{
			return atanf(value);
		}

		inline float Max(float valueA, float valueB)
		{
			return (valueA > valueB) ? valueA : valueB;
		}

		inline float Min(float valueA, float valueB)
		{
			return (valueA < valueB) ? valueA : valueB;
		}

		inline float DegToRad(float value)
		{
			return (float)value * PI / 180.0f;
		}

		inline float RadToDeg(float value)
		{
			return (float)value * 180.0f / PI;
		}
	}
}

#endif
