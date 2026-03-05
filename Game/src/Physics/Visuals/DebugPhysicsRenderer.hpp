#ifndef DEBUGPHYSICSRENDERER_HPP
#define DEBUGPHYSICSRENDERER_HPP
#include <irrlicht.h>
#include <vector>

namespace physics
{
	class Rigidbody;
	class Collider;
}

class DebugPhysicsRenderer
{
public:
	DebugPhysicsRenderer(irr::scene::ISceneManager* p_sceneManager);

	void AddRigidbody(physics::Rigidbody* p_body);
	void AddCollider(physics::Collider* p_collider);

	void Sync();
private:
	irr::scene::ISceneManager* m_sceneManager;

	struct BodyVisual
	{
		physics::Rigidbody* body = nullptr;
		irr::scene::ISceneNode* node = nullptr;
	};

	struct ColliderVisual
	{
		physics::Collider* collider = nullptr;
		irr::scene::ISceneNode* node = nullptr;
	};

	std::vector<BodyVisual> m_bodyVisuals;
	std::vector<ColliderVisual> m_colliderVisuals;
};

#endif // !DEBUGPHYSICSRENDERER_HPP

