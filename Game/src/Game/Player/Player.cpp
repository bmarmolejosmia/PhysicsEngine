#include "Player.h"
#include "../Scene/IScene.h"
#include "../Physics/Physics.h"

#include <irrlicht.h>
#include <cmath>

namespace game
{
	Player::Player(irr::scene::ISceneNode* p_node, irr::scene::ICameraSceneNode* p_camera)
		: m_node(p_node), m_camera(p_camera), m_moveSpeed(15.0f), 
		m_cameraYaw(0.0f), m_cameraPitch(0.0f), m_cameraDistance(10.0f)
	{
		m_lastMousePosition = irr::core::vector2di(0, 0);
	}

	void Player::Update(float p_deltaTime, const GameContext& p_context)
	{
		if (!m_node || !m_camera || !p_context.input) { return; }

		Movement(p_deltaTime, p_context);
		UpdateCamera(p_context);
	}

	void Player::Movement(float p_deltaTime, const GameContext& p_context)
	{
		// Safety check: ensure the physics system exists
		if (!p_context.physics) return;

		irr::core::vector3df pos = m_node->getPosition();

		// Calculate forward and right vectors relative to the camera
		irr::core::vector3df forward = pos - m_camera->getPosition();
		forward.Y = 0.0f;
		forward.normalize();

		irr::core::vector3df right(forward.Z, 0.0f, -forward.X);
		irr::core::vector3df movement(0, 0, 0);

		// Apply WASD input
		if (p_context.input->IsKeyDown(irr::KEY_KEY_W)) movement += forward;
		if (p_context.input->IsKeyDown(irr::KEY_KEY_S)) movement -= forward;
		if (p_context.input->IsKeyDown(irr::KEY_KEY_A)) movement -= right;
		if (p_context.input->IsKeyDown(irr::KEY_KEY_D)) movement += right;

		// 1. Setup the velocity we *want* to achieve this frame
		irr::core::vector3df desiredVelocity(0, 0, 0);

		// 2. Handle horizontal walking and rotation
		if (movement.getLengthSQ() > 0.0f)
		{
			movement.Y = 0.0f;
			movement.normalize();

			// Store the intended X and Z movement
			desiredVelocity.X = movement.X * m_moveSpeed * p_deltaTime;
			desiredVelocity.Z = movement.Z * m_moveSpeed * p_deltaTime;

			// Smooth rotation (Keep this exactly the same)
			float targetAngle = atan2(movement.X, movement.Z) * irr::core::RADTODEG;
			float currentAngle = m_node->getRotation().Y;

			float diff = targetAngle - currentAngle;
			while (diff < -180.0f) diff += 360.0f;
			while (diff > 180.0f) diff -= 360.0f;

			float turnSpeed = 15.0f * p_deltaTime;
			if (turnSpeed > 1.0f) turnSpeed = 1.0f;

			float newAngle = currentAngle + (diff * turnSpeed);
			m_node->setRotation(irr::core::vector3df(0, newAngle, 0));
		}

		// 3. Add gravity to the desired velocity (Applies every frame, even when standing still)
		float gravityForce = -9.81f;
		desiredVelocity.Y = gravityForce * p_deltaTime;

		// ==========================================
		// 4. PHYSICS RESOLUTION (Step C)
		// ==========================================

		// Grab the character's physical bounds
		irr::core::aabbox3df playerBox = m_node->getTransformedBoundingBox();

		// Ask the physics system to clip the velocity against walls and floors
		irr::core::vector3df actualVelocity = p_context.physics->MoveKinematic(playerBox, desiredVelocity);

		// Apply the safe, collision-checked velocity to the character
		pos += actualVelocity;
		m_node->setPosition(pos);
	}

	void Player::UpdateCamera(const GameContext& p_context)
	{
		const Input::SMouseState& mouseState = p_context.input->GetMouseState();
		
		if (mouseState.RightButtonDown)
		{
			float deltaX = static_cast<float>(mouseState.Position.X - m_lastMousePosition.X);
			float deltaY = static_cast<float>(mouseState.Position.Y - m_lastMousePosition.Y);

			float sensitivity = 0.4f;
			
			if (m_invertCamera)
			{
				m_cameraYaw -= deltaX * sensitivity;
				m_cameraPitch += deltaY * sensitivity;
			}
			else
			{
				m_cameraYaw += deltaX * sensitivity;
				m_cameraPitch += deltaY * sensitivity;
			}

			if (m_cameraPitch > 85.0f) { m_cameraPitch = 85.0f; }
			if (m_cameraPitch < -10.0f) { m_cameraPitch = -10.0f; }
		}

		m_lastMousePosition = mouseState.Position;

		irr::core::vector3df playerPosition = m_node->getPosition();
		
		float radYaw = irr::core::degToRad(m_cameraYaw);
		float radPitch = irr::core::degToRad(m_cameraPitch);

		irr::core::vector3df cameraOffset;
		
		cameraOffset.X = m_cameraDistance * cos(radPitch) * sin(radYaw);
		cameraOffset.Y = m_cameraDistance * sin(radPitch);
		cameraOffset.Z = m_cameraDistance * cos(radPitch) * cos(radYaw);
		
		m_camera->setPosition(playerPosition + cameraOffset);
		m_camera->setTarget(playerPosition);
	}
}