#ifndef PHYSICSWORLD_HPP
#define PHYSICSWORLD_HPP

#include <vector>
#include "..\Utilities\PhysicsTypes.hpp"
#include "..\Rigidbody\Rigidbody.hpp"

namespace physics
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld() = default;

		void SetGravity(const Vector3& gravity);
		const Vector3& GetGravity() const;

		void SetFixedTimeStep(float p_deltaTime);
		float GetFixedTimeStep() const;

		void AddRigidbody(Rigidbody* p_body);
		void RemoveRigidbody(Rigidbody* p_body);

		void StepSimulation(float p_deltaTime);
	private:
		void Step(float p_deltaTime);
		std::vector<Rigidbody*> m_bodies;

		Vector3 m_gravity;

		float m_fixedTimeStep;
		float m_timeAccumulator;
	};
}

#endif // !PHYSICSWORLD_HPP
