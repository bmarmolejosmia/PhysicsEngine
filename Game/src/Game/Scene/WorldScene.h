#ifndef WORLDSCENE_H
#define WORLDSCENE_H

#include "IScene.h"
#include "../Player/Player.h"

#include <memory>

namespace game
{
	class WorldScene : public IScene
	{
	public:
		void OnEnter(GameContext* p_context) override;
		void Update(float p_deltaTime, const GameContext& p_context) override;
		void Render(const GameContext& p_context) override;
		void OnExit(GameContext* p_context) override;

	private:
		irr::scene::ISceneNode* m_floorNode;
		irr::scene::ISceneNode* m_cubeNode;
		irr::scene::ISceneNode* m_sphereNode;
		irr::scene::ICameraSceneNode* m_cameraNode;

		std::unique_ptr<Player> m_player;
	};
}

#endif // !WORLDSCENE_H

