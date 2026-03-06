#include "PhysicsWorld.hpp"
#include <algorithm>

namespace physics
{
	PhysicsWorld::PhysicsWorld() : m_registeredRigidBodies()
		, m_registeredColliders()
		, m_gravity(0.0f, -9.81f, 0.0f)
	{

	}

	PhysicsWorld::~PhysicsWorld()
	{

	}

	void PhysicsWorld::RegisterRigidbody(RigidBody* p_rigidBody)
	{
		if (p_rigidBody == nullptr)
		{
			return;
		}

		const auto existingRigidBodyIterator = std::find(m_registeredRigidBodies.begin(), m_registeredRigidBodies.end(), p_rigidBody);
		if (existingRigidBodyIterator != m_registeredRigidBodies.end())
		{
			return;
		}

		m_registeredRigidBodies.push_back(p_rigidBody);
	}

	void PhysicsWorld::UnregisterRigidbody(RigidBody* p_rigidBody)
	{
		if (p_rigidBody == nullptr)
		{
			return;
		}

		const auto existingRigidBodyIterator = std::find(m_registeredRigidBodies.begin(), m_registeredRigidBodies.end(), p_rigidBody);
		if (existingRigidBodyIterator == m_registeredRigidBodies.end())
		{
			return;
		}

		m_registeredRigidBodies.erase(existingRigidBodyIterator);
	}

	void PhysicsWorld::RegisterCollider(Collider* p_collider)
	{
		if (p_collider == nullptr)
		{
			return;
		}

		const auto existingColliderIterator = std::find(m_registeredColliders.begin(), m_registeredColliders.end(), p_collider);
		if (existingColliderIterator != m_registeredColliders.end())
		{
			return;
		}

		m_registeredColliders.push_back(p_collider);
	}

	void PhysicsWorld::UnregisterCollider(Collider* p_collider)
	{
		if (p_collider == nullptr)
		{
			return;
		}

		const auto existingColliderIterator = std::find(m_registeredColliders.begin(), m_registeredColliders.end(), p_collider);
		if (existingColliderIterator == m_registeredColliders.end())
		{
			return;
		}

		m_registeredColliders.erase(existingColliderIterator);
	}

	void PhysicsWorld::SetGravity(const Vector3& p_gravity)
	{
		m_gravity = p_gravity;
	}

	const Vector3& PhysicsWorld::GetGravity() const
	{
		return m_gravity;
	}

	void PhysicsWorld::Step(float p_deltaTime)
	{
		(void)p_deltaTime;
	}

	const std::vector<RigidBody*>& PhysicsWorld::GetRegisteredRigidBodies() const
	{
		return m_registeredRigidBodies;
	}

	const std::vector<Collider*>& PhysicsWorld::GetRegisteredColliders() const
	{
		return m_registeredColliders;
	}
}