
#include "Asteroid.h"
#include "Constants.h"

Asteroid::Asteroid() :
	m_Points{},
	m_Position((float)GetHalfScreenWidth(), (float)GetHalfScreenHeight()),
	m_Velocity(Vector2::Zero),
	m_AngularVelocity(0.0f),
	m_Radians(Math::RandomFloat(0.0f, MAX_RADIANS)),
	m_Radius(MAX_RADIUS),
	m_isActive(false)
{

	//this spawns the asteroid on either the left side or the bottom of the screen
	int whereSpawn = Math::RandomInt(0, 1);

	if (whereSpawn == 0)
	{
		setPosition(Math::RandomFloat(0.0f, (float)GetScreenWidth()), !Math::RandomFloat(0.0f, (float)GetScreenHeight()));

	}else if (whereSpawn == 1)
	{
		setPosition(!Math::RandomFloat(0.0f, (float)GetScreenWidth()), Math::RandomFloat(0.0f, (float)GetScreenHeight()));

	}


	//random numbers of sides
	int numSides = Math::RandomInt(MIN_NUM_OF_SIDES, MAX_NUM_OF_SIDES);

	float radiansPerSide = 2.0f * (float)M_PI / (float)numSides;

	for (int i = 0; i < numSides; i++)
	{
		//random radius for each point
		float radius = Math::RandomFloat(MIN_RADIUS, MAX_RADIUS);

		//creates the point
		float angle = i * radiansPerSide;
		Vector2 point = Vector2(cos(angle), sin(angle)) * radius;
		//pushes point onto the vector to create the asteroid
		m_Points.push_back(point);
	}
	//Add one last point to connect back to the first point to create the connected asteroid and activate it
	m_Points.push_back(m_Points[0]);
	m_isActive = true;

	//Initialize liniar velocity 
	float angleRadians = Math::RandomFloat(0, (float)M_PI * 2);
	Vector2 direction = Vector2(cos(angleRadians), sin(angleRadians));
	m_Velocity = direction * Math::RandomFloat(MIN_SPEED_A, MAX_SPEED_A);

	//Initialize angular velocity 
	m_AngularVelocity = Math::RandomFloat(MIN_A_SPEED_A, MAX_A_SPEED_A);

}

void Asteroid::OnUpdate(float delta)
{
	if (m_isActive)
	{
		//turn
		m_Radians += m_AngularVelocity * delta;

		//Move
		m_Position += m_Velocity * delta;


		//used for wrapping the asteroid across the screen
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
	

}

void Asteroid::OnRender(BatchRenderer& batchRenderer)
{
	if (m_isActive)
	{
		batchRenderer.RenderLineStrip(m_Points, ColorList::White, 2.0f, m_Position, 0.0f);
	}

}

void Asteroid::Colided()
{
	m_isActive = false;
}

Vector2 Asteroid::setPosition(Vector2 v)
{
	m_Position = v;
	return m_Position;
}

Vector2 Asteroid::setPosition(float w, float h)
{
	m_Position.x = w;
	m_Position.y = h;
	return m_Position;
}

bool Asteroid::IsActive()
{
	return m_isActive;
}

float Asteroid::getRadius()
{
	return m_Radius;
}

Vector2 Asteroid::getPosition()
{
	return m_Position;
}
