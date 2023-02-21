#pragma once

#include <GameDev2D.h>
#include "Ship.h"
#include "Asteroid.h"
#include "Constants.h"
#include "Laser.h"
#include "Shield.h"



namespace GameDev2D
{
	class Game
	{
	public:
		Game();
		~Game();

		//Write game logic in the Update method
		void OnUpdate(float delta);

		//Render game objects in the Draw method
		void OnRender(BatchRenderer& batchRenderer);

		//Input event methods
		void OnKeyEvent(KeyCode keyCode, KeyState keyState);
		void OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY);
		void OnMouseMovedEvent(float mouseX, float mouseY);

		void SpawnLaser(const Vector2& position, const Vector2& velocity);
		void SpawnShield(const Vector2& position);

	private:
		Laser* GetLaserFromPool();
		Shield* GetShieldFromPool();
		SpriteFont m_Text;
		SpriteFont m_Text2;
		//Member variables GO HERE 
		Ship* m_Ship;
		std::vector <Asteroid> m_Asteroid;
		Laser* m_Lasers[LASER_POOL_SIZE];
		Shield* m_Shields[SHEILD_POOL_SIZE];
		int m_asteroidsDestroyed;
		float m_Time;
		bool m_GameOver;
	};
}
