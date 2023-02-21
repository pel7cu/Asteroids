
#include "Shield.h"
#include "Constants.h"
namespace GameDev2D
{
	//the shield was made with 2 stages the diamond stage when dropped from asteroids and the active stage when the player picks up a diamond
	Shield::Shield():
		m_Points{ {0.0f, 12.5f}, {12.5f, 0.0f} , {0.0f, -12.5f}, {-12.5, 0.0f}, {0.0f, 12.5f} },
		m_Radians(0.0f),
		m_OrbitRadius(30.0f),
		m_Active(false),
		m_IsCollected(false),
		m_OrbitVelocity(1.0f),
		m_Pos1(Vector2::Zero),
		m_Pos2(Vector2::Zero),
		m_Pos3(Vector2::Zero),
		m_Radius(12.5),
		m_isDiamond(false),
		m_Time(0.0f)
	{

	}

	Shield::~Shield()
	{

	}

	void Shield::Colide()
	{
		m_Active = false;
	}

	Vector2 Shield::setPosition(Vector2 p)
	{
		m_Position = p;
		return m_Position;
	}

	Vector2 Shield::getPosition()
	{
		return m_Position;
	}

	float Shield::getRadius()
	{
		return m_Radius;
	}

	bool Shield::beingUsed()
	{
		return m_Active;
	}

	void Shield::setUsed(bool b)
	{
		m_Active = b;
	}

	void Shield::Activate(const Vector2& position)
	{
		m_isDiamond = true;
		m_Time = 0.0f;
		m_Position = position;
		
	}

	void Shield::OnUpdate(float delta)
	{

		//times it for 20sec then deactivates it
		m_Time += delta;
		if (m_Time > DIAMOND_ACTIVE_TIME)
		{
			m_isDiamond = false;
			m_Time = 0.0f;
		}

		//rotation of the three dots
		m_Radians += Math::DegreesToRadians(360 / 180 * m_OrbitVelocity);

		m_Pos1.x = (m_Position.x + cosf(m_Radians) * m_OrbitRadius);
		m_Pos1.y = (m_Position.y + sinf(m_Radians) * m_OrbitRadius);
		m_Pos2.x = (m_Position.x + cosf(m_Radians + 2.0944) * m_OrbitRadius); //2.0944 is 120 degre offset
		m_Pos2.y = (m_Position.y + sinf(m_Radians + 2.0944) * m_OrbitRadius);//2.0944 is 120 degre offset
		m_Pos3.x = (m_Position.x + cosf(m_Radians + 4.18879) * m_OrbitRadius);//4.18879 is 240 degre offset
		m_Pos3.y = (m_Position.y + sinf(m_Radians + 4.18879) * m_OrbitRadius);//4.18879 is 240 degre offset





	}

	void Shield::OnRender(BatchRenderer& batchRenderer)
	{
		//renders either a diamond or 3 dots or none
		if (m_Active)
		{
			batchRenderer.RenderCircle(m_Pos1, 3.0f, ColorList::Blue);
			batchRenderer.RenderCircle(m_Pos2, 3.0f, ColorList::Blue);
			batchRenderer.RenderCircle(m_Pos3, 3.0f, ColorList::Blue);
		}
		if (m_isDiamond)
		{
			batchRenderer.RenderLineStrip(m_Points, ColorList::White, 2.0f, m_Position, 0.0f);
		}



	}
	bool Shield::isDiamond()
	{
		return m_isDiamond;
	}
	void Shield::setIsDiamond(bool b)
	{
		m_isDiamond = b;
	}
}