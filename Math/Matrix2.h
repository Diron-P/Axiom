#ifndef MATRIX2_H
#define MATRIX2_H

#include "Vector2.h"

namespace Axiom
{
	namespace Math
	{
		class Matrix2
		{
		public:
			float m[2][2];

			Matrix2();
			Matrix2(const float& num1, const float& num2, const float& num3, const float& num4);
			Matrix2(const Vector2& v1, const Vector2& v2);

			Matrix2& Identity();
			Vector2 GetColumn(int i) const;
			Matrix2& SetColumn(int i, const Vector2& column);

			Matrix2& operator*=(const Matrix2& n);
			friend Matrix2 operator*(const float& scalar, const Matrix2& m1);
			friend Matrix2 operator*(const Matrix2& m1, const Matrix2& m2);
			friend bool operator==(const Matrix2& m1, const Matrix2& m2);
			friend bool operator!=(const Matrix2& m1, const Matrix2& m2);
		};

		inline Matrix2& Matrix2::Identity()
		{
			m[0][0] = m[1][1] = 1.0f;
			return *this;
		}

		inline Vector2 Matrix2::GetColumn(int i) const
		{
			return Vector2(m[0][i], m[1][i]);
		}

		inline Matrix2& Matrix2::SetColumn(int i, const Vector2& column)
		{
			m[0][i] = column.x;
			m[1][i] = column.y;

			return *this;
		}

		inline Matrix2::Matrix2()
		{
			// TODO
			// memset(m, 0, sizeof(m[0][0]) * 2 * 2);
		}

		inline Matrix2::Matrix2(const float& num1, const float& num2, const float& num3, const float& num4)
		{
			m[0][0] = num1;
			m[0][1] = num3;
			m[1][0] = num2;
			m[1][1] = num4;
		}

		inline Matrix2::Matrix2(const Vector2& v1, const Vector2& v2)
		{
			m[0][0] = v1.x;
			m[0][1] = v1.y;
			m[1][0] = v2.x;
			m[1][1] = v2.y;
		}

		inline Matrix2& Matrix2::operator*=(const Matrix2& n)
		{
			//Column 1
			Vector2 col1(m[0][0], m[1][0]);
			m[0][0] = col1.x * n.m[0][0] + col1.y * n.m[0][1];
			m[1][0] = col1.x * n.m[1][0] + col1.y * n.m[1][1];

			//Column 2
			Vector2 col2(m[0][1], m[1][1]);
			m[0][1] = col2.x * n.m[0][0] + col2.y * n.m[0][1];
			m[1][1] = col2.x * n.m[1][0] + col2.y * n.m[1][1];

			return *this;
		}

		inline Matrix2 operator*(const float& scalar, const Matrix2& m1)
		{
			return Matrix2(
				scalar * m1.m[0][0], scalar * m1.m[0][1],
				scalar * m1.m[1][0], scalar * m1.m[1][1]);
		}

		inline Matrix2 operator*(const Matrix2& m1, const Matrix2& m2)
		{
			return Matrix2(
				m1.m[0][0] * m2.m[0][0] + m1.m[1][0] * m2.m[0][1],
				m1.m[0][0] * m2.m[1][0] + m1.m[1][0] * m2.m[1][1],
				m1.m[0][1] * m2.m[0][0] + m1.m[1][1] * m2.m[0][1],
				m1.m[0][1] * m2.m[1][0] + m1.m[1][1] * m2.m[1][1]);
		}

		inline bool operator==(const Matrix2& m1, const Matrix2& m2)
		{
			return (m1.m[0][0] == m2.m[0][0]) && (m1.m[0][1] == m2.m[0][1]) && (m1.m[1][0] == m2.m[1][0]) && (m1.m[1][1] == m2.m[1][1]);
		}

		inline bool operator!=(const Matrix2& m1, const Matrix2& m2)
		{
			return (m1.m[0][0] != m2.m[0][0]) || (m1.m[0][1] != m2.m[0][1]) || (m1.m[1][0] != m2.m[1][0]) || (m1.m[1][1] != m2.m[1][1]);
		}

		inline Matrix2 Transpose(const Matrix2& m1)
		{
			return Matrix2(
				m1.m[0][0], m1.m[1][0],
				m1.m[0][1], m1.m[1][1]);
		}

		inline float Determinant(const Matrix2& m1)
		{
			return m1.m[0][0] * m1.m[1][1] - m1.m[0][1] * m1.m[1][0];
		}

		Matrix2 Inverse(const Matrix2& m1)
		{
			float Determinant = m1.m[0][0] * m1.m[1][1] - m1.m[1][0] * m1.m[0][1];

			float inversedDet = 1.0f / Determinant;

			return Matrix2(
				+m1.m[1][1] * inversedDet,
				-m1.m[1][0] * inversedDet,
				-m1.m[0][1] * inversedDet,
				+m1.m[0][0] * inversedDet);
		}
	}	// end namespace Math
}	// end namespace Axiom

#endif
