#pragma once

#include <GameDev2D.h>

using namespace GameDev2D;

class Asteroid
{
public:
	Asteroid();

	void OnUpdate(float delta);
	void OnRender(BatchRenderer& batchRenderer);
	void Colided();

	Vector2 setPosition(Vector2 v);
	Vector2 setPosition(float w, float h);

	bool IsActive();
	float getRadius();
	Vector2 getPosition();

private:
	std::vector<Vector2> m_Points;
	Vector2 m_Position;
	Vector2 m_Velocity;
	float m_AngularVelocity;
	float m_Radians;
	float m_Radius;
	bool m_isActive;

};

