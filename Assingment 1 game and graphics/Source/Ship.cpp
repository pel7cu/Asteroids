#include "Ship.h"
#include "Constants.h"
#include "Game.h"
namespace GameDev2D
{

	Ship::Ship(Game* game,	const Vector2& position) :
		m_Game(game),
		m_Points{ {-15.0f, 10.0f}, {15.0f, 0.0f},{-15.0f,-10.0f},{-10.0f,0.0f},{-15.0f,10.0f} },
		m_Position(position),
		m_Velocity(Vector2::Zero),
		m_Radians(0.0f),
		m_Radius(15.0f)
	{

	}

	void Ship::OnUpdate(float delta)
	{
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
		//if (m_Position.y < 0)
		//{
		//	m_Position.y += GetScreenHeight();
		//}




		if (IsKeyDown(KeyCode::A))
		{
			m_Radians += ANGULAR_VELOCITY * delta;
		}
		if (IsKeyDown(KeyCode::D))
		{
			m_Radians -= ANGULAR_VELOCITY * delta;
		}

		if (IsKeyDown(KeyCode::W))
		{
			Vector2 acceleration = Vector2(cos(m_Radians), sin(m_Radians)) * RATE_OF_ACCELERATION;
			m_Velocity += acceleration * delta; //vf = vi + a * t	
			
		}



		Vector2 displacement = m_Velocity * delta;
		m_Position += displacement;

		//Cap the velocity if its going too fast
		if (m_Velocity.Length() > MAX_SPEED_S)
		{
			m_Velocity = m_Velocity.Normalized() * MAX_SPEED_S;
		}


		//Set the speed as the output
	

	}

	void Ship::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.RenderLineStrip(m_Points, ColorList::White, 2.0f, m_Position, m_Radians);
	}

	void Ship::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		if (keyState == KeyState::Down)
		{
			if (keyCode == KeyCode::Space)
			{
				//fire a laser

				Vector2 direction(cos(m_Radians), sin(m_Radians));
				Vector2 position = m_Position + direction;
				Vector2 velocity = direction * LASER_SPEED;

				m_Game->SpawnLaser(position, velocity);


			}
		}
	}

	void Ship::respawn()
	{
		m_Position.x = Math::RandomFloat(0, GetScreenWidth());
		m_Position.y = Math::RandomFloat(0, GetScreenHeight());
		m_Velocity = Vector2::Zero;
	}


	Vector2 Ship::setPosition(Vector2 v)
	{
		m_Position = v;
		return m_Position;
	}

	Vector2 Ship::setPosition(float w, float h)
	{
		m_Position.x = w;
		m_Position.y = h;
		return m_Position;
	}

	Vector2 Ship::setVelocity(Vector2 velocity)
	{
		m_Velocity = velocity;
		return m_Velocity;
	}

	float Ship::getRadius()
	{
		return m_Radius;
	}

	Vector2 Ship::getPosition()
	{
		return m_Position;
	}

}