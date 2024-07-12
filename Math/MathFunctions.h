#ifndef MATH_FUNCTIONS_H
#define MATH_FUNCTIONS_H

#include <math.h>

//PI defines
#define PI 3.14159265359f 

namespace Axiom
{
	namespace Math
	{
		//Trigonometric Functions
		inline float Sin(float fValue)
		{
			return sinf(fValue);
		}

		inline float Cos(float fValue)
		{
			return cosf(fValue);
		}

		inline float Tan(float fValue)
		{
			return tanf(fValue);
		}

		inline float ASin(float fValue)
		{
			return asinf(fValue);
		}

		inline float ACos(float fValue)
		{
			return acosf(fValue);
		}

		inline float ATan(float fValue)
		{
			return atanf(fValue);
		}

		inline float Max(float fValueA, float fValueB)
		{
			return (fValueA > fValueB) ? fValueA : fValueB;
		}

		inline float Min(float fValueA, float fValueB)
		{
			return (fValueA < fValueB) ? fValueA : fValueB;
		}

		inline float DegToRad(float fValue)
		{
			return (float)fValue * PI / 180.0f;
		}

		inline float RadToDeg(float fValue)
		{
			return (float)fValue * 180.0f / PI;
		}
	}
}

#endif
