#pragma once
#include <GameDev2D.h>

namespace GameDev2D
{

	class Laser
	{
	public:
		Laser();

		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);

		Vector2 getPosition();
		float getRadius();

		void Colided();

		void Activate(const Vector2& position, const Vector2& velocity);
		bool IsActive();
		void setIsActive(bool b);


	private:
		std::vector<Vector2> m_Points;
		Vector2 m_Position;
		Vector2 m_Velocity;
		float m_Radians;
		bool m_IsActive;
		float m_Radius;
		float m_Time;

	};

}

