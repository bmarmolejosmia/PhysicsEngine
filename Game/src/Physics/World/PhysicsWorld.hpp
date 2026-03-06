#ifndef PHYSICSWORLD_HPP
#define PHYSICSWORLD_HPP
#include <vector>
#include "..\Utilities\PhysicsTypes.hpp"

namespace physics
{
	class RigidBody;
	class Collider;

	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld();

		void RegisterRigidbody(RigidBody* p_rigidBody);
		void UnregisterRigidbody(RigidBody* p_rigidBody);

		void RegisterCollider(Collider* p_collider);
		void UnregisterCollider(Collider* p_collider);

		void SetGravity(const Vector3& p_gravity);
		const Vector3& GetGravity() const;

		void Step(float p_deltaTime);

		const std::vector<RigidBody*>& GetRegisteredRigidBodies() const;
		const std::vector<Collider*>& GetRegisteredColliders() const;
	private:
		std::vector<RigidBody*> m_registeredRigidBodies;
		std::vector<Collider*> m_registeredColliders;

		Vector3 m_gravity;
	};
}

#endif // !PHYSICSWORLD_HPP


