#include "PhysicsWorld.hpp"
#include <algorithm>
#include <cstdio>

namespace physics
{
	PhysicsWorld::PhysicsWorld() : m_bodies()
								, m_colliders()
								, m_gravity(0.0f, -9.81f, 0.0f)
								, m_fixedTimeStep(1.0f / 60.0f)
								, m_timeAccumulator(0.0f)
	{
	}

	void PhysicsWorld::SetGravity(const Vector3& p_gravity)
	{
		m_gravity = p_gravity;
	}
	const Vector3& PhysicsWorld::GetGravity() const
	{
		return m_gravity;
	}

	void PhysicsWorld::SetFixedTimeStep(float p_deltaTime)
	{
		if (p_deltaTime > 0.0f)
		{
			m_fixedTimeStep = p_deltaTime;
		}
	}
	float PhysicsWorld::GetFixedTimeStep() const
	{
		return m_fixedTimeStep;
	}

	void PhysicsWorld::AddRigidbody(Rigidbody* p_body)
	{
		if (!p_body)
		{
			return;
		}

		auto iterator = std::find(m_bodies.begin(), m_bodies.end(), p_body);
		if (iterator == m_bodies.end())
		{
			m_bodies.push_back(p_body);
		}
	}
	void PhysicsWorld::RemoveRigidbody(Rigidbody* p_body)
	{
		if (!p_body)
		{
			return;
		}

		auto iterator = std::find(m_bodies.begin(), m_bodies.end(), p_body);
		if (iterator != m_bodies.end())
		{
			m_bodies.erase(iterator);
		}
	}

	void PhysicsWorld::AddCollider(Collider* p_collider)
	{
		if (!p_collider)
		{
			return;
		}

		auto iterator = std::find(m_colliders.begin(), m_colliders.end(), p_collider);
		if(iterator == m_colliders.end())
		{
			m_colliders.push_back(p_collider);
		}
	}

	void PhysicsWorld::RemoveCollider(Collider* p_collider)
	{
		if (!p_collider)
		{
			return;
		}

		auto iterator = std::find(m_colliders.begin(), m_colliders.end(), p_collider);
		if (iterator != m_colliders.end())
		{
			m_colliders.erase(iterator);
		}
	}

	void PhysicsWorld::StepSimulation(float p_deltaTime)
	{
		if (p_deltaTime <= 0.0f)
		{
			return;
		}

		m_timeAccumulator += p_deltaTime;

		while (m_timeAccumulator >= m_fixedTimeStep)
		{
			Step(m_fixedTimeStep);
			m_timeAccumulator -= m_fixedTimeStep;
		}
	}

	void PhysicsWorld::Step(float p_deltaTime)
	{
		for (Rigidbody* body : m_bodies)
		{
			if (!body || body->IsStatic())
			{
				continue;
			}

			body->AddForce(m_gravity * body->GetMass());
			body->IntegrateVelocity(p_deltaTime);
		}

		printf("Colliders: %zu\n", m_colliders.size());

		std::vector<CollisionPair> collisionPairs;
		Broadphase::ComputeCollisionPairs(m_colliders, collisionPairs);
		printf("Pairs: %zu\n", collisionPairs.size());

		for (const CollisionPair& pair : collisionPairs)
		{
			printf("Pair: A=%d B=%d\n",
				   (int)pair.first->GetType(),
				   (int)pair.second->GetType());
		}

		std::vector<Contact> contacts;
		Narrowphase::GenerateContacts(collisionPairs, contacts);
		printf("Contacts: %zu\n", contacts.size());

		for (const Contact& contact : contacts)
		{
			printf("Penetration: %f\n", contact.penetration);
		}

		CollisionResolver::ResolveContacts(contacts);

		for (Rigidbody* body : m_bodies)
		{
			if (!body || body->IsStatic())
			{
				continue;
			}

			body->IntegratePosition(p_deltaTime);
		}
	}
}