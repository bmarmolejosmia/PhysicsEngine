#include "Rigidbody.hpp"
#include <cmath>

namespace physics
{
	Rigidbody::Rigidbody() : m_position(0.0f, 0.0f, 0.0f)
							, m_rotation(0.0f, 0.0f, 0.0f, 1.0f)
							, m_velocity(0.0f, 0.0f, 0.0f)
							, m_angularVelocity(0.0f, 0.0f, 0.0f)
							, m_forceAccumulator(0.0f, 0.0f, 0.0f)
							, m_torqueAccumulator(0.0f, 0.0f, 0.0f)
							, m_mass(1.0f)
							, m_inverseMass(1.0f)
							, m_inertia(1.0f)
							, m_inverseInertia(1.0f)
	{

	}

	void Rigidbody::SetMass(float p_mass)
	{
		m_mass = p_mass;

		if (m_mass <= 0.0f)
		{
			m_mass = 0.0f;
			m_inverseMass = 0.0f;
		}
		else
		{
			m_inverseMass = 1.0f / m_mass;
		}
	}
	float Rigidbody::GetMass() const
	{
		return m_mass;
	}
	float Rigidbody::GetInverseMass() const
	{
		return m_inverseMass;
	}

	void Rigidbody::SetInertia(float p_inertia)
	{
		m_inertia = p_inertia;

		if (m_inertia <= 0.0f)
		{
			m_inertia = 0.0f;
			m_inverseInertia = 0.0f;
		}
		else
		{
			m_inverseInertia = 1.0f / m_inertia;
		}
	}
	float Rigidbody::GetInverseInertia() const
	{
		return m_inverseInertia;
	}
	float Rigidbody::GetInertia() const
	{
		return m_inertia;
	}

	bool Rigidbody::IsStatic() const
	{
		return m_inverseMass == 0.0f;
	}
	
	void Rigidbody::AddForce(const Vector3& p_force)
	{
		m_forceAccumulator += p_force;
	}
	void Rigidbody::AddTorque(const Vector3& p_torque)
	{
		m_torqueAccumulator += p_torque;
	}

	void Rigidbody::ClearAccumulators()
	{
		m_forceAccumulator.set(0.0f, 0.0f, 0.0f);
		m_torqueAccumulator.set(0.0f, 0.0f, 0.f);
	}

	void Rigidbody::IntegrateVelocity(float p_deltaTime)
	{
		if (p_deltaTime <= 0.0f || IsStatic())
		{
			ClearAccumulators();
			return;
		}

		const Vector3 acceleration = m_forceAccumulator * m_inverseMass;
		m_velocity += acceleration * p_deltaTime;

		const float dampingPerSecond = 0.5f;
		m_velocity *= std::pow(1.0f - dampingPerSecond, p_deltaTime);
		
		ClearAccumulators();
	}

	void Rigidbody::IntegratePosition(float p_deltaTime)
	{
		if (p_deltaTime <= 0.0f || IsStatic())
			return;

		m_position += m_velocity * p_deltaTime;
	}


	/*void Rigidbody::Integrate(float p_deltaTime)
	{
		//Prevent invalid integration
		if (p_deltaTime <= 0.0f || IsStatic())
		{
			ClearAccumulators();
			return;
		}

		const Vector3 acceleration = m_forceAccumulator * m_inverseMass;
		m_velocity += acceleration * p_deltaTime;
		m_position += m_velocity * p_deltaTime;

		const Vector3 angularAcceleration = m_torqueAccumulator * m_inverseInertia;
		m_angularVelocity += angularAcceleration * p_deltaTime;

		const float angularSpeed = m_angularVelocity.getLength();

		if (angularSpeed > 0.00001f)
		{
			Vector3 axis = m_angularVelocity / angularSpeed;
			const float angle = angularSpeed * p_deltaTime;

			Quat deltaRotation;
			deltaRotation.fromAngleAxis(angle, axis);

			m_rotation = deltaRotation * m_rotation;
			m_rotation.normalize();
		}

		ClearAccumulators();
	}*/
}