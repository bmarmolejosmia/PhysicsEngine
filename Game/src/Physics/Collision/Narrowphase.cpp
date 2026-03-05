#include "Narrowphase.hpp"
#include "Collider.hpp"
#include "..\Rigidbody\Rigidbody.hpp"
#include <cmath>

namespace physics
{
	static bool TestSphereSphere(Collider* p_colliderA, Collider* p_colliderB, Contact& p_outContact)
	{
		const Vector3 positionA = p_colliderA->GetBody()->GetPosition() + p_colliderA->GetOffset();
		const Vector3 positionB = p_colliderB->GetBody()->GetPosition() + p_colliderB->GetOffset();

		const float radiusA = p_colliderA->Sphere().radius;
		const float radiusB = p_colliderB->Sphere().radius;

		const Vector3 delta = positionB - positionA;
		const float distanceSquared = delta.getLengthSQ();
		const float combinedRadius = radiusA + radiusB;

		if (distanceSquared >= combinedRadius * combinedRadius)
		{
			return false;
		}

		const float distance = std::sqrt(distanceSquared);

		p_outContact.colliderA = p_colliderA;
		p_outContact.colliderB = p_colliderB;

		if (distance > 0.0001f)
		{
			p_outContact.normal = delta / distance;
		}
		else
		{
			p_outContact.normal = Vector3(0.0f, 1.0f, 0.0f);
		}

		p_outContact.penetration = combinedRadius - distance;
		p_outContact.point = positionA + p_outContact.normal * radiusA;

		p_outContact.isTrigger = p_colliderA->IsTrigger() || p_colliderB->IsTrigger();

		return true;
	}

	void Narrowphase::GenerateContacts(const std::vector<CollisionPair>& p_collisionPairs, std::vector<Contact>& p_outContacts)
	{
		p_outContacts.clear();

		for (const CollisionPair& collisionPair : p_collisionPairs)
		{
			Collider* colliderA = collisionPair.first;
			Collider* colliderB = collisionPair.second;

			if (!colliderA || !colliderB)
			{
				continue;
			}

			if (colliderA->GetType() == ShapeType::Sphere && colliderB->GetType() == ShapeType::Sphere)
			{
				Contact contact;
				if (TestSphereSphere(colliderA, colliderB, contact))
				{
					p_outContacts.push_back(contact);
				}
			}
		}
	}
}