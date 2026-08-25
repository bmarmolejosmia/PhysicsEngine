#include "Physics.h"

namespace game
{
	void Physics::AddStaticCollider(const irr::core::aabbox3df& p_box)
	{
		m_staticColliders.push_back(p_box);
	}

	irr::core::vector3df Physics::MoveKinematic(irr::core::aabbox3df p_playerBox, irr::core::vector3df p_velocity)
	{
		irr::core::vector3df allowedVelocity = p_velocity;
		irr::core::aabbox3df testBox;

		// A tiny margin to prevent the box from snagging on surfaces it is sliding against
		const float skinWidth = 0.02f;

		// ==========================================
		// 1. Test X-Axis Movement
		// ==========================================
		testBox = p_playerBox;
		testBox.MinEdge.X += allowedVelocity.X;
		testBox.MaxEdge.X += allowedVelocity.X;

		// Shrink Y and Z so sliding along the floor/walls doesn't trigger a false collision
		testBox.MinEdge.Y += skinWidth; testBox.MaxEdge.Y -= skinWidth;
		testBox.MinEdge.Z += skinWidth; testBox.MaxEdge.Z -= skinWidth;

		for (const auto& collider : m_staticColliders) {
			if (testBox.intersectsWithBox(collider)) {
				allowedVelocity.X = 0.0f; // Hit a wall on the X axis
				break;
			}
		}
		// Apply safe X movement before testing Z
		p_playerBox.MinEdge.X += allowedVelocity.X;
		p_playerBox.MaxEdge.X += allowedVelocity.X;

		// ==========================================
		// 2. Test Z-Axis Movement
		// ==========================================
		testBox = p_playerBox;
		testBox.MinEdge.Z += allowedVelocity.Z;
		testBox.MaxEdge.Z += allowedVelocity.Z;

		// Shrink Y and X
		testBox.MinEdge.Y += skinWidth; testBox.MaxEdge.Y -= skinWidth;
		testBox.MinEdge.X += skinWidth; testBox.MaxEdge.X -= skinWidth;

		for (const auto& collider : m_staticColliders) {
			if (testBox.intersectsWithBox(collider)) {
				allowedVelocity.Z = 0.0f; // Hit a wall on the Z axis
				break;
			}
		}
		// Apply safe Z movement before testing Y
		p_playerBox.MinEdge.Z += allowedVelocity.Z;
		p_playerBox.MaxEdge.Z += allowedVelocity.Z;

		// ==========================================
		// 3. Test Y-Axis Movement
		// ==========================================
		testBox = p_playerBox;
		testBox.MinEdge.Y += allowedVelocity.Y;
		testBox.MaxEdge.Y += allowedVelocity.Y;

		// Shrink X and Z so falling down against a wall doesn't snag
		testBox.MinEdge.X += skinWidth; testBox.MaxEdge.X -= skinWidth;
		testBox.MinEdge.Z += skinWidth; testBox.MaxEdge.Z -= skinWidth;

		for (const auto& collider : m_staticColliders) {
			if (testBox.intersectsWithBox(collider)) {
				allowedVelocity.Y = 0.0f; // Hit the floor or a ceiling
				break;
			}
		}

		return allowedVelocity;
	}

	void Physics::ClearColliders()
	{
		m_staticColliders.clear();
	}
}