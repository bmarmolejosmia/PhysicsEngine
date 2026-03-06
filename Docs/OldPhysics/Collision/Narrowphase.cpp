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

	static bool TestSphereAABB(Collider* sphere, Collider* box, Contact& outContact)
	{
		const Vector3 sphereCenter = sphere->GetBody()->GetPosition() + sphere->GetOffset();
		const Vector3 boxCenter = box->GetBody()->GetPosition() + box->GetOffset();
		const Vector3 half = box->Box().halfSize;

		const Vector3 min = boxCenter - half;
		const Vector3 max = boxCenter + half;

		Vector3 closestPoint;
		closestPoint.X = std::max(min.X, std::min(sphereCenter.X, max.X));
		closestPoint.Y = std::max(min.Y, std::min(sphereCenter.Y, max.Y));
		closestPoint.Z = std::max(min.Z, std::min(sphereCenter.Z, max.Z));

		const Vector3 delta = sphereCenter - closestPoint;
		const float distanceSq = delta.getLengthSQ();
		const float radius = sphere->Sphere().radius;

		if (distanceSq > radius * radius) 
		{
			return false;
		}

		const float distance = std::sqrt(distanceSq);

		outContact.colliderA = sphere;
		outContact.colliderB = box;
		outContact.normal = (distance > 0.0001f) ? (-delta / distance) : Vector3(0, 1, 0);
		outContact.penetration = radius - distance;
		outContact.point = closestPoint;
		outContact.isTrigger = sphere->IsTrigger() || box->IsTrigger();

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
				continue;

			const ShapeType typeA = colliderA->GetType();
			const ShapeType typeB = colliderB->GetType();

			if (typeA == ShapeType::Sphere && typeB == ShapeType::Sphere)
			{
				Contact contact;
				if (TestSphereSphere(colliderA, colliderB, contact))
				{
					p_outContacts.push_back(contact);
				}
			}
			else if (typeA == ShapeType::Sphere && typeB == ShapeType::Box)
			{
				Contact contact;
				if (TestSphereAABB(colliderA, colliderB, contact))
				{
					p_outContacts.push_back(contact);
				}
			}
			else if (typeA == ShapeType::Box && typeB == ShapeType::Sphere)
			{
				Contact contact;
				if (TestSphereAABB(colliderB, colliderA, contact))
				{
					// Flip normal so it still points A → B
					std::swap(contact.colliderA, contact.colliderB);
					contact.normal = -contact.normal;
					p_outContacts.push_back(contact);
				}
			}
		}
	}

}