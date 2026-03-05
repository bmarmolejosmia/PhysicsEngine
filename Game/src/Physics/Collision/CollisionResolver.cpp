#include "CollisionResolver.hpp"
#include "Contact.hpp"
#include "Collider.hpp"
#include "..\Rigidbody\Rigidbody.hpp"

#include <algorithm>
#include <cmath>

namespace physics
{
	static float GetMaxFloat(float p_valueA, float p_valueB)
	{
		return (p_valueA > p_valueB) ? p_valueA : p_valueB;
	}

	static void ApplyPositionalCorrection(Rigidbody* p_bodyA, Rigidbody* p_bodyB, const Contact& p_contact)
	{
		const float inverseMassA = p_bodyA->GetInverseMass();
		const float inverseMassB = p_bodyB->GetInverseMass();
		const float totalInverseMass = inverseMassA + inverseMassB;

		if (totalInverseMass <= 0.0f)
		{
			return;
		}

		const float correctionPercent = 0.15f;
		const float penetrationTolerance = 0.01f;

		const float correctedPenetration = GetMaxFloat(p_contact.penetration - penetrationTolerance, 0.0f);
		if (correctedPenetration <= 0.0f)
		{
			return;
		}

		const Vector3 correctionVector = p_contact.normal * (correctedPenetration * correctionPercent / totalInverseMass);
		p_bodyA->SetPosition(p_bodyA->GetPosition() - correctionVector * inverseMassA);
		p_bodyB->SetPosition(p_bodyB->GetPosition() + correctionVector * inverseMassB);

		printf("Correcting penetration\n");
	}

	static void ApplyNormalImpulse(Rigidbody* p_bodyA, Rigidbody* p_bodyB, const Contact& p_contact)
	{
		const float inverseMassA = p_bodyA->GetInverseMass();
		const float inverseMassB = p_bodyB->GetInverseMass();
		const float totalInverseMass = inverseMassA + inverseMassB;

		if (totalInverseMass <= 0.0f) 
		{
			return;
		}

		const Vector3 velocityA = p_bodyA->GetVelocity();
		const Vector3 velocityB = p_bodyB->GetVelocity();
		const Vector3 relativeVelocity = velocityB - velocityA;

		const float relativeSpeedAlongNormal = relativeVelocity.dotProduct(p_contact.normal);

		// If bodies are separating along the normal, do nothing
		if (relativeSpeedAlongNormal > 0.0f) 
		{
			return;
		}

		float restitution = 0.2f;

		// Reduce bounce for slow contacts to help resting stability
		if (std::fabs(relativeSpeedAlongNormal) < 0.25f) 
		{
			Vector3 velocityA = p_bodyA->GetVelocity();
			Vector3 velocityB = p_bodyB->GetVelocity();

			velocityA -= p_contact.normal * velocityA.dotProduct(p_contact.normal);
			velocityB -= p_contact.normal * velocityB.dotProduct(p_contact.normal);

			p_bodyA->SetVelocity(velocityA);
			p_bodyB->SetVelocity(velocityB);
			return;
		}

		const float impulseMagnitude = -(1.0f + restitution) * relativeSpeedAlongNormal / totalInverseMass;

		const Vector3 impulseVector = p_contact.normal * impulseMagnitude;

		p_bodyA->SetVelocity(velocityA - impulseVector * inverseMassA);
		p_bodyB->SetVelocity(velocityB + impulseVector * inverseMassB);
	}

	void CollisionResolver::ResolveContacts(std::vector<Contact>& p_contacts)
	{
		for (const Contact& currentContact : p_contacts)
		{
			if (currentContact.colliderA == nullptr || currentContact.colliderB == nullptr) 
			{
				continue;
			}

			if (currentContact.isTrigger) 
			{
				continue;
			}

			Rigidbody* bodyA = currentContact.colliderA->GetBody();
			Rigidbody* bodyB = currentContact.colliderB->GetBody();

			if (bodyA == nullptr || bodyB == nullptr) 
			{
				continue;
			}

			const float totalInverseMass = bodyA->GetInverseMass() + bodyB->GetInverseMass();
			if (totalInverseMass <= 0.0f) 
			{
				continue;
			}

			ApplyPositionalCorrection(bodyA, bodyB, currentContact);
			ApplyNormalImpulse(bodyA, bodyB, currentContact);
		}
	}
}
