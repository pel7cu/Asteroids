#include <GameDev2D.h>
namespace GameDev2D
{
	class Shield
	{
	public:
		Shield();
		~Shield();

		void Colide();

		Vector2 setPosition(Vector2 p);
		Vector2 getPosition();
		float getRadius();

		bool beingUsed();
		void setUsed(bool b);

		void Activate(const Vector2& position);
		void OnUpdate(float delta);
		void OnRender(BatchRenderer& batchRenderer);

		bool isDiamond();
		void setIsDiamond(bool b);


	private:
		std::vector<Vector2> m_Points;
		Vector2 m_Position;
		Vector2 m_Pos1;
		Vector2 m_Pos2;
		Vector2 m_Pos3;
		bool m_IsCollected;
		bool m_Active;
		bool m_isDiamond;
		float m_Radians;
		float m_OrbitRadius;
		float m_OrbitVelocity;
		float m_Time;
		float m_Radius;
	};

}

