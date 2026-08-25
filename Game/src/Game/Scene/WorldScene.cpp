#include "WorldScene.h"
#include "../Physics/Physics.h"

namespace game
{
	void WorldScene::OnEnter(GameContext* p_context)
	{
		m_floorNode = p_context->smgr->addCubeSceneNode(1.0f);
		if (m_floorNode)
		{
			m_floorNode->setPosition(irr::core::vector3df(0, 0, 0));
			m_floorNode->setScale(irr::core::vector3df(50, 1, 50));
			m_floorNode->setMaterialFlag(irr::video::EMF_LIGHTING, true);
			
			m_floorNode->updateAbsolutePosition();

			p_context->physics->AddStaticCollider(m_floorNode->getTransformedBoundingBox());
		}

		m_cubeNode = p_context->smgr->addCubeSceneNode(1.0f);
		if (m_cubeNode)
		{
			m_cubeNode->setPosition(irr::core::vector3df(2, 3.0f, 5));
			m_cubeNode->setScale(irr::core::vector3df(1, 1, 1));
			m_cubeNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		}

		m_sphereNode = p_context->smgr->addSphereSceneNode(1.0f);
		if (m_sphereNode)
		{
			m_sphereNode->setPosition(irr::core::vector3df(-5, 2.0f, 2));
			m_sphereNode->setScale(irr::core::vector3df(1, 1, 1));
			m_sphereNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
		}

		m_cameraNode = p_context->smgr->addCameraSceneNode();
		if (m_cubeNode && m_cameraNode)
		{
			m_player = std::make_unique<Player>(m_cubeNode, m_cameraNode);
		}
	}

	void WorldScene::Update(float p_deltaTime, const GameContext& p_context)
	{
		if (m_player)
		{
			m_player->Update(p_deltaTime, p_context);
		}
	}

	void WorldScene::Render(const GameContext& p_context)
	{
		p_context.smgr->drawAll();
		p_context.guienv->drawAll();
	}

	void WorldScene::OnExit(GameContext* p_context)
	{
		p_context->physics->ClearColliders();

		p_context->smgr->clear();
		p_context->guienv->clear();
	}
}