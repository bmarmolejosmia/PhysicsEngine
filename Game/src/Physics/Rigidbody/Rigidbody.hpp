#ifndef RIGIDBODY_HPP
#define RIGIDBODY_HPP
#include "..\Utilities\PhysicsTypes.hpp"

namespace physics
{
	class Rigidbody
	{
	public:
		Rigidbody();
		~Rigidbody() = default;

		void SetInertia(float p_inertia);
		void SetMass(float p_mass);
		void ClearAccumulators();
		void Integrate(float p_deltaTime);
		void AddForce(const Vector3& p_force);
		void AddTorque(const Vector3& p_torque);

		float GetMass() const;
		float GetInverseMass() const;
		float GetInertia() const;
		float GetInverseInertia() const;

		bool IsStatic() const;

		const Vector3& GetPosition() const 
		{ 
			return m_position; 
		}
		void SetPosition(const Vector3& p_position) 
		{
			m_position = p_position;
		}

		const Quat& GetRotation() const
		{
			return m_rotation;
		}
		void SetRotation(const Quat& p_rotation)
		{
			m_rotation = p_rotation;
		}

		const Vector3& GetVelocity() const
		{
			return m_velocity;
		}
		void SetVelocity(const Vector3& p_velocity)
		{
			m_velocity = p_velocity;
		}

		const Vector3& GetAngularVelocity() const
		{
			return m_angularVelocity;
		}
		void SetAngularVelocity(const Vector3& p_angularVelocity)
		{
			m_angularVelocity = p_angularVelocity;
		}
	private:
		Quat m_rotation;

		Vector3 m_position;
		Vector3 m_velocity;
		Vector3 m_angularVelocity;

		float m_mass;
		float m_inverseMass;
		float m_inertia;
		float m_inverseInertia;

		Vector3 m_forceAccumulator;
		Vector3 m_torqueAccumulator;
	};
}

#endif // !RIGIDBODY_HPP

