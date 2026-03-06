#include "DebugPhysicsRenderer.hpp"
#include "..\Rigidbody\Rigidbody.hpp"
#include "..\Collision\Collider.hpp"

using namespace irr;

DebugPhysicsRenderer::DebugPhysicsRenderer(scene::ISceneManager* p_sceneManager) : m_sceneManager(p_sceneManager)
{
}

void DebugPhysicsRenderer::AddRigidbody(physics::Rigidbody* p_body)
{
	if (!p_body)
	{
		return;
	}

	scene::ISceneNode* node = m_sceneManager->addSphereSceneNode(0.25f);

	if (!node)
	{
		return;
	}

	node->setMaterialFlag(video::EMF_LIGHTING, false);
	m_bodyVisuals.push_back({ p_body, node });
}

void DebugPhysicsRenderer::AddCollider(physics::Collider* p_collider)
{
	if (!p_collider)
	{
		return;
	}

	scene::ISceneNode* node = nullptr;

	switch (p_collider->GetType())
	{
		case physics::ShapeType::Sphere:
			node = m_sceneManager->addSphereSceneNode(p_collider->Sphere().radius);
			break;
		case physics::ShapeType::Box:
			const physics::Vector3& halfSize = p_collider->Box().halfSize;
			node = m_sceneManager->addCubeSceneNode(1.0f);
			node->setScale(physics::Vector3(halfSize.X * 2.0f,
											halfSize.Y * 2.0f,
											halfSize.Z * 2.0f));
			break;
	}

	if (!node)
	{
		return;
	}

	node->setMaterialFlag(video::EMF_WIREFRAME, true);
	m_colliderVisuals.push_back({ p_collider, node });
}

void DebugPhysicsRenderer::AddRigidbody(physics::Rigidbody* p_body, irr::scene::ISceneNode* p_node)
{
	if (!p_body || !p_node)
	{
		return;
	}

	m_bodyVisuals.push_back({ p_body, p_node });
}


void DebugPhysicsRenderer::Sync()
{
	for (BodyVisual& visual : m_bodyVisuals)
	{
		const physics::Vector3& position = visual.body->GetPosition();

		visual.node->setPosition(position);
	}

	for (ColliderVisual& visual : m_colliderVisuals)
	{
		physics::Rigidbody* body = visual.collider->GetBody();
		if (!body)
		{
			continue;
		}

		const physics::Vector3 worldPosition = body->GetPosition() + visual.collider->GetOffset();
		visual.node->setPosition(worldPosition);
	}
}