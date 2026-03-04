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

		Quat rotation;

		Vector3 position;
		Vector3 velocity;
		Vector3 angularVelocity;
	private:
		float m_mass;
		float m_inverseMass;
		float m_inertia;
		float m_inverseInertia;

		Vector3 m_forceAccumulator;
		Vector3 m_torqueAccumulator;
	};
}

#endif // !RIGIDBODY_HPP

