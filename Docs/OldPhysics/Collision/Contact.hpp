#ifndef CONTACT_HPP
#define CONTACT_HPP
#include "..\Utilities\PhysicsTypes.hpp"

namespace physics
{
	class Collider;

	struct Contact
	{
		Collider* colliderA = nullptr;
		Collider* colliderB = nullptr;

		Vector3 normal = Vector3(0.0f, 1.0f, 0.0f);

		float penetration = 0.0f;

		Vector3 point = Vector3(0.0f, 0.0f, 0.0f);

		bool isTrigger = false;
	};
}

#endif // !CONTACT_HPP

