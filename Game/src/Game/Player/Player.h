#ifndef PLAYER_H
#define PLAYER_H

#include <vector2d.h>
#include "../Simulation/LifeStats.h"

namespace irr
{
	namespace scene
	{
		class ISceneNode;
		class ICameraSceneNode;
	}
}

namespace game
{
	struct GameContext;

	class Player
	{
	public:
		Player(irr::scene::ISceneNode* p_node, irr::scene::ICameraSceneNode* p_camera);
		~Player() = default;

		void Update(float p_deltaTime, const GameContext& p_context);

		irr::scene::ISceneNode* GetNode() const { return m_node; }
		const LifeStats& GetStats() const { return m_stats; }
	
	private:
		void Movement(float p_deltaTime, const GameContext& p_context);
		void UpdateCamera(const GameContext& p_context);

		irr::scene::ISceneNode* m_node;
		irr::scene::ICameraSceneNode* m_camera;

		//Player Variables
		float m_moveSpeed;
		LifeStats m_stats;

		//Camera Variables
		float m_cameraYaw;
		float m_cameraPitch;
		float m_cameraDistance;
		irr::core::vector2di m_lastMousePosition;

		bool m_invertCamera = false;
	};
}

#endif // !PLAYER_H

