#include "Camera.h"
#include "Math/MathFunctions.h"

Axiom::Camera::Camera()
{
}

void Axiom::Camera::Initialize(const Vector3& position)
{
	m_initialPosition = position;

}

void Axiom::Camera::Update(float elapsedSeconds)
{
	Vector3 move(0.0f, 0.0f, 0.0f);

	if (fabs(move.x) > 0.1f && fabs(move.z) > 0.1f)
	{
		// TODO
	}

	float moveInterval = m_moveSpeed * elapsedSeconds;
	float rotateInterval = m_turnSpeed * elapsedSeconds;

	m_pitch = Min(m_pitch, PIDIV4);
    m_pitch = Max(-PIDIV4, m_pitch);

	float x = move.x * -Cos(m_yaw) - move.z * Sin(m_yaw);
	float z = move.x * Sin(m_yaw) - move.z * Cos(m_yaw);
	m_position.x += x * moveInterval;
	m_position.z += z * moveInterval;

	float r = Cos(m_pitch);
	m_lookDirection.x = r * Sin(m_yaw);
	m_lookDirection.y = Sin(m_pitch);
	m_lookDirection.z = r * Cos(m_yaw);
}
