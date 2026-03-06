#ifndef PHYSICSWORLD_HPP
#define PHYSICSWORLD_HPP

#include <vector>
#include "..\Utilities\PhysicsTypes.hpp"
#include "..\Rigidbody\Rigidbody.hpp"
#include "..\Collision\Collider.hpp"
#include "..\Collision\Broadphase.hpp"
#include "..\Collision\Narrowphase.hpp"
#include "..\Collision\CollisionResolver.hpp"


namespace physics
{
	class PhysicsWorld
	{
	public:
		PhysicsWorld();
		~PhysicsWorld() = default;

		void SetGravity(const Vector3& p_gravity);
		const Vector3& GetGravity() const;

		void SetFixedTimeStep(float p_deltaTime);
		float GetFixedTimeStep() const;

		void AddRigidbody(Rigidbody* p_body);
		void RemoveRigidbody(Rigidbody* p_body);

		void AddCollider(Collider* p_collider);
		void RemoveCollider(Collider* p_collider);

		void StepSimulation(float p_deltaTime);
	private:
		void Step(float p_deltaTime);
		
		std::vector<Rigidbody*> m_bodies;
		std::vector<Collider*> m_colliders;

		Vector3 m_gravity;

		float m_fixedTimeStep;
		float m_timeAccumulator;
	};
}

#endif // !PHYSICSWORLD_HPP
