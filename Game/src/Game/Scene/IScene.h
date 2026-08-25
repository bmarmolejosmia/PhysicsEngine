#ifndef ISCENE_H
#define ISCENE_H

#include <irrlicht.h>
#include "../Utils/Input.h"

namespace game
{
	class Physics;

	struct GameContext
	{
		irr::IrrlichtDevice* device;
		irr::video::IVideoDriver* driver;
		irr::scene::ISceneManager* smgr;
		irr::gui::IGUIEnvironment* guienv;
		Input* input;
		Physics* physics;
	};

	class IScene
	{
	public:
		virtual ~IScene() = default;
		virtual void OnEnter(GameContext* p_context) = 0;
		virtual void Update(float p_deltaTime,const GameContext& p_context) = 0;
		virtual void Render(const GameContext& p_context) = 0;
		virtual void OnExit(GameContext* p_context) = 0;
	};
}

#endif // !ISCENE_H

