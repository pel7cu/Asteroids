#pragma once

#include <GameDev2D.h>

namespace GameDev2D 
{
	//forward declaration
	class Game;

	class Ship
	{
	public:
		Ship(Game* game, const Vector2& position);
		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);

		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void respawn();

		Vector2 setPosition(Vector2 v);
		Vector2 setPosition(float w, float h);
		Vector2 setVelocity(Vector2 velocity);

		float getRadius();
		Vector2 getPosition();

	private:
		Game* m_Game;
		std::vector<Vector2> m_Points;
		Vector2 m_Position;
		Vector2 m_Velocity;
		float m_Radians;
		float m_Radius;

	};

}





