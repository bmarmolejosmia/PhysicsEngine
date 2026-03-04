#include "PhysicsWorld.hpp"
#include <algorithm>

namespace physics
{
	PhysicsWorld::PhysicsWorld() : m_bodies()
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
			body->Integrate(p_deltaTime);
		}
	}
}