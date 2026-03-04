#include "Rigidbody.hpp"

namespace physics
{
	Rigidbody::Rigidbody() : position(0.0f, 0.0f, 0.0f)
							, rotation(0.0f, 0.0f, 0.0f, 1.0f)
							, velocity(0.0f, 0.0f, 0.0f)
							, angularVelocity(0.0f, 0.0f, 0.0f)
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

	void Rigidbody::Integrate(float p_deltaTime)
	{
		//Prevent invalid integration
		if (p_deltaTime <= 0.0f || IsStatic())
		{
			ClearAccumulators();
			return;
		}

		const Vector3 acceleration = m_forceAccumulator * m_inverseMass;
		velocity += acceleration * p_deltaTime;
		position += velocity * p_deltaTime;

		const Vector3 angularAcceleration = m_torqueAccumulator * m_inverseInertia;
		angularVelocity += angularAcceleration * p_deltaTime;

		const float angularSpeed = angularVelocity.getLength();

		if (angularSpeed > 0.00001f)
		{
			Vector3 axis = angularVelocity / angularSpeed;
			const float angle = angularSpeed * p_deltaTime;

			Quat deltaRotation;
			deltaRotation.fromAngleAxis(angle, axis);

			rotation = deltaRotation * rotation;
			rotation.normalize();
		}

		ClearAccumulators();
	}
}