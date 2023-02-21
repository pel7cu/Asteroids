
#include "Laser.h"
#include "Constants.h"

namespace GameDev2D
{
	Laser::Laser() :
		m_Points{ },
		m_Position(Vector2::Zero),
		m_Velocity(Vector2::Zero),
		m_IsActive(false),
		m_Radians(m_Velocity.Angle()),
		m_Radius(5.0f),
		m_Time(0.0f)
	{
		int size = 3;

		int numSides = 8;
		float radiansPerSide = 2.0f * (float)M_PI / (float)numSides;

		for (int i = 0; i < numSides; i++)
		{
			float angle = i * radiansPerSide;

			Vector2 point = Vector2(cos(angle), sin(angle)) * size;

			m_Points.push_back(point);
		}

		m_Points.push_back(m_Points[0]);

	}

	void Laser::OnUpdate(float delta)
	{

		//moves if its active
		if (m_IsActive)
		{
			m_Position += m_Velocity * delta;

		}



		//times it for 2 sec then deactivates the bullet
		m_Time += delta;
		if (m_Time > LASER_ACTIVE_TIME)
		{
			m_IsActive = false;
			m_Time = 0.0f;
		}
		

		//warping if goes out of bounds
		if (m_Position.x >= (float)GetScreenWidth())
		{
			m_Position.x -= GetScreenWidth();
		}
		if (m_Position.x < 0)
		{
			m_Position.x += GetScreenWidth();
		}
		if (m_Position.y > (float)GetScreenHeight())
		{
			m_Position.y -= GetScreenHeight();
		}
		if (m_Position.y < 0)
		{
			m_Position.y += GetScreenHeight();
		}



	}

	void Laser::OnRender(BatchRenderer& batchRenderer)
	{
		if (m_IsActive)
		{
			batchRenderer.RenderLineStrip(m_Points, ColorList::White, 2.0f, m_Position, m_Radians);
		}
	}

	Vector2 Laser::getPosition()
	{
		return m_Position;
	}
	float Laser::getRadius()
	{
		return m_Radius;
	}
	void Laser::Colided()
	{
		m_IsActive = false;
	}
	void Laser::Activate(const Vector2& position, const Vector2& velocity)
	{
		m_IsActive = true;
		m_Time = 0.0f;
		m_Position = position;
		m_Velocity = velocity;
	}

	bool Laser::IsActive()
	{
		return m_IsActive;
	}
	void Laser::setIsActive(bool b)
	{
		m_IsActive = b;
	}
}

