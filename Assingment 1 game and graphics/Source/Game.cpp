#include "Ship.h"
#include "Asteroid.h"
#include "Game.h"
#include "Constants.h"


namespace GameDev2D
{
	Game::Game() :
		m_Ship(nullptr),
		m_Asteroid(NUM_OF_ASTEROIDS),
		m_Lasers{},
		m_Shields{},
		m_Text("OpenSans-CondBold_32"),
		m_Text2("OpenSans-CondBold_32"),
		m_asteroidsDestroyed(0),
		m_Time(0.0f),
		m_GameOver(false)

	{
		// text
		m_Text.SetPosition((float)GetHalfScreenWidth(), (float)GetHalfScreenHeight());
		m_Text.SetAnchor(0.0f, 0.0f);
		m_Text2.SetPosition((float)GetHalfScreenWidth(), (float)GetHalfScreenHeight() + 30);
		m_Text2.SetAnchor(0.0f, 0.0f);


		m_Ship = new Ship(this, Vector2(GetHalfScreenWidth(), GetHalfScreenHeight()));

		//create all objects needed
		for (int i = 0; i < LASER_POOL_SIZE; i++)
		{
			m_Lasers[i] = new Laser();
		}

		//create all objects needed
		for (int i = 0; i < SHEILD_POOL_SIZE; i++)
		{
			m_Shields[i] = new Shield();
		}

	}

	Game::~Game()
	{
		if (m_Ship != nullptr)
		{
			delete m_Ship;
			m_Ship = nullptr;
		}



		//laser
		for (int i = 0; i < LASER_POOL_SIZE; i++)
		{
			if (m_Lasers[i] != nullptr)
			{
				delete m_Lasers[i];
				m_Lasers[i] = nullptr;
			}
		}

		//Shield
		for (int i = 0; i < SHEILD_POOL_SIZE; i++)
		{
			if (m_Shields[i] != nullptr)
			{
				delete m_Shields[i];
				m_Shields[i] = nullptr;
			}
		}
	}

	void Game::OnUpdate(float delta)
	{
		//if the games not over add more to the timer
		if (!m_GameOver)
		{
			m_Time += delta;
		}



		//updates for all game objects
		m_Ship->OnUpdate(delta);
		for (int i = 0; i < NUM_OF_ASTEROIDS; i++)
		{
			m_Asteroid[i].OnUpdate(delta);
		}

		for (int i = 0; i < SHEILD_POOL_SIZE; i++)
		{
			m_Shields[i]->OnUpdate(delta);
		}

		//colision for ship and A
		for (Asteroid& a : m_Asteroid)
		{
			if (a.IsActive())
			{
				float distanceSquared = (a.getPosition().x - m_Ship->getPosition().x) * (a.getPosition().x - m_Ship->getPosition().x) + (a.getPosition().y - m_Ship->getPosition().y) * (a.getPosition().y - m_Ship->getPosition().y);
				float radiiSquared = (m_Ship->getRadius() + a.getRadius()) * (m_Ship->getRadius() + a.getRadius());
				bool didCollide = (distanceSquared <= radiiSquared);

				if (didCollide)//if ship and asteroid colided
				{
					bool shieldActive = false;

					for (int i = 0; i < SHEILD_POOL_SIZE; i++)//checks for a shield
					{
						if (m_Shields[i]->beingUsed() == true)
						{
						    m_Shields[i]->setPosition(Vector2(1000, 1000));
							m_Shields[i]->setUsed(false);
							shieldActive = true;
							a.Colided();
							m_asteroidsDestroyed++;
							break;
						}

					}

					if (shieldActive == false)
					{
						m_Ship->respawn();
					
					}
					


				}
			}

		}
		//colition for laser and A
		for (int i = 0; i < LASER_POOL_SIZE; i++)
		{
			m_Lasers[i]->OnUpdate(delta);
			for (Asteroid& a : m_Asteroid)
			{
				if (m_Lasers[i]->IsActive() && a.IsActive())
				{


					float distanceSquared = (a.getPosition().x - m_Lasers[i]->getPosition().x) * (a.getPosition().x - m_Lasers[i]->getPosition().x) + (a.getPosition().y - m_Lasers[i]->getPosition().y) * (a.getPosition().y - m_Lasers[i]->getPosition().y);
					float radiiSquared = (m_Lasers[i]->getRadius() + a.getRadius()) * (m_Lasers[i]->getRadius() + a.getRadius());
					bool didCollide = (distanceSquared <= radiiSquared);

					if (didCollide)//if laser and asteroid colided
					{
						int rand = Math::RandomFloat(1, 7);
						if (rand == 1)
						{
							SpawnShield(a.getPosition());
						}
						
						m_Lasers[i]->Colided();
						a.Colided();
						m_asteroidsDestroyed++;

					}

				}
			}

		}

		//colition for sheild and ship
		for (int i = 0; i < SHEILD_POOL_SIZE; i++)
		{
			float distanceSquared = (m_Ship->getPosition().x - m_Shields[i]->getPosition().x) * (m_Ship->getPosition().x - m_Shields[i]->getPosition().x) + (m_Ship->getPosition().y - m_Shields[i]->getPosition().y) * (m_Ship->getPosition().y - m_Shields[i]->getPosition().y);
			float radiiSquared = (m_Shields[i]->getRadius() + m_Ship->getRadius()) * (m_Shields[i]->getRadius() + m_Ship->getRadius());
			bool didCollide = (distanceSquared <= radiiSquared);

			if (didCollide)
			{
				m_Shields[i]->setIsDiamond(false);
				m_Shields[i]->setUsed(true);

			}

			if (m_Shields[i]->beingUsed())
			{
				m_Shields[i]->setPosition(m_Ship->getPosition());
			}
		}



		//if all the asteroids are gone end the game
		if (m_asteroidsDestroyed == NUM_OF_ASTEROIDS)

		{
			m_GameOver = true;
			std::string output = std::to_string(m_Time);
			m_Text.SetText(output);
			
			m_Text2.SetText("You Won! it took you in seconds:");

		

		}





	}

	void Game::OnRender(BatchRenderer& batchRenderer)
	{
		batchRenderer.BeginScene();


		batchRenderer.RenderSpriteFont(m_Text);
		batchRenderer.RenderSpriteFont(m_Text2);

		if (!m_GameOver)
		{


			m_Ship->OnRender(batchRenderer);


			for (int i = 0; i < NUM_OF_ASTEROIDS; i++)
			{
				m_Asteroid[i].OnRender(batchRenderer);
			}



			for (int i = 0; i < LASER_POOL_SIZE; i++)
			{
				m_Lasers[i]->OnRender(batchRenderer);

			}


			for (int i = 0; i < SHEILD_POOL_SIZE; i++)
			{
				m_Shields[i]->OnRender(batchRenderer);

			}
		}


		batchRenderer.EndScene();
	}

	void Game::OnKeyEvent(KeyCode keyCode, KeyState keyState)
	{
		m_Ship->OnKeyEvent(keyCode, keyState);
	}

	void Game::OnMouseButtonEvent(MouseButton button, MouseButtonState state, float mouseX, float mouseY)
	{

	}

	void Game::OnMouseMovedEvent(float mouseX, float mouseY)
	{

	}
	void Game::SpawnLaser(const Vector2& position, const Vector2& velocity)
	{
		Laser* laser = GetLaserFromPool();
		if (laser != nullptr)
		{
			laser->Activate(position, velocity);
		}

	}

	Laser* Game::GetLaserFromPool()
	{
		for (int i = 0; i < LASER_POOL_SIZE; i++)
		{
			if (m_Lasers[i]->IsActive() == false)
			{
				return m_Lasers[i];
			}
		}
		return nullptr;
	}

	Shield* Game::GetShieldFromPool()
	{
		for (int i = 0; i < SHEILD_POOL_SIZE; i++)
		{
			if (m_Shields[i]->isDiamond() == false)
			{
				return m_Shields[i];
			}
		}
		return nullptr;
	}

	void Game::SpawnShield(const Vector2& position)
	{
		Shield* shield = GetShieldFromPool();
		if (shield != nullptr)
		{
			shield->Activate(position);
		}
	}
}