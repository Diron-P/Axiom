#ifndef CAMERA_H
#define CAMERA_H

#include "Math/Matrix4.h"

namespace Axiom
{
	using namespace Math;

	class Camera
	{
	public:
		Camera();
		~Camera();

		void Initialize(const Vector3& position);
		void Update(float elapsedSeconds);

		void GetViewMatrix();

	private:
		float m_yaw;
		float m_pitch;
		float m_moveSpeed;
		float m_turnSpeed;

		Vector3 m_initialPosition;
		Vector3 m_position;
		Vector3 m_lookDirection;
		Vector3 m_upDirection;

		Matrix4 m_viewMatrix;
	};
}

#endif // !CAMERA_H
