#ifndef GAME_H
#define GAME_H

#include "Utils/Input.h"
#include "Physics/Physics.h"

#include <memory>

namespace irr
{
	class IrrlichtDevice;

	namespace video
	{
		class IVideoDriver;
	}
	namespace scene
	{
		class ISceneManager;
	}
	namespace gui
	{
		class IGUIEnvironment;
	}
}

namespace game
{	
	class IScene;
	struct GameContext;

	class Game
	{
	public:
		Game();
		~Game();

		void Initialize();
		void Run();

		void ChangeScene(std::unique_ptr<IScene> p_newScene);
		GameContext GetContext();

	private:
		bool CreateWindow();
		irr::IrrlichtDevice* m_device;

		Input m_input;
		Physics m_physics;
		std::unique_ptr<game::IScene> m_currentScene;

		float m_deltaTime;
	};
}

#endif // !GAME_H


