#include "Game.h"
#include "Scene/IScene.h"
#include "Scene/WorldScene.h"

#include <irrlicht.h>

namespace game
{
	Game::Game() : m_device(0)
	{
		m_deltaTime = 0.0f;
	}

	Game::~Game()
	{
		if (m_device) { m_device->drop(); }
	}

	void Game::Initialize()
	{

	}

	void Game::Run()
	{
		if (!CreateWindow())
		{
			return;
		}

		Initialize();

		irr::ITimer* timer = m_device->getTimer();
		irr::u32 then = timer->getTime();

		while (m_device->run())
		{
			const irr::u32 now = timer->getTime();
			m_deltaTime = (float)(now - then) / 1000.0f;
			then = now;

			if (m_deltaTime > 0.1f) { m_deltaTime = 0.1f; }

			GameContext context = GetContext();

			if (m_currentScene)
			{
				m_currentScene->Update(m_deltaTime, context);
			}

			context.driver->beginScene(true, true, irr::video::SColor(255, 125, 125, 255));
			
			if (m_currentScene)
			{
				m_currentScene->Render(context);
			}

			context.driver->endScene();
		}
	}

	void Game::ChangeScene(std::unique_ptr<IScene> p_newScene)
	{
		GameContext context = GetContext();
		if(m_currentScene)
		{
			m_currentScene->OnExit(&context);
		}

		m_currentScene = std::move(p_newScene);

		if (m_currentScene)
		{
			m_currentScene->OnEnter(&context);
		}
	}

	GameContext Game::GetContext()
	{
		return GameContext{m_device, m_device->getVideoDriver(), m_device->getSceneManager(), m_device->getGUIEnvironment(), &m_input, &m_physics};
	}

	bool Game::CreateWindow()
	{
		m_device = irr::createDevice(irr::video::EDT_OPENGL, irr::core::vector2d<irr::u32>(1366, 768), 16, false, false, false, &m_input);
		
		if (!m_device)
		{
			return false;
		}

		ChangeScene(std::make_unique<WorldScene>());
		return true;
	}

}