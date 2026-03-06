#ifndef COLLIDER_HPP
#define COLLIDER_HPP
#include "..\Utilities\PhysicsTypes.hpp"
#include "AABB.hpp"

namespace physics
{
	class Rigidbody;

	enum class ShapeType
	{
		Sphere,
		Box
	};

	struct SphereShape
	{
		float radius = 1.0f;
	};

	struct BoxShape
	{
		Vector3 halfSize = Vector3(0.5f, 0.5f, 0.5f);
	};

	class Collider
	{
	public:
		Collider(Rigidbody* p_body, ShapeType p_type);
		
		ShapeType GetType() const { return m_type; }
		SphereShape& Sphere() { return m_sphere; }
		const SphereShape& Sphere() const { return m_sphere; }

		BoxShape& Box() { return m_box; }
		const BoxShape& Box() const {	return m_box; }

		void SetTrigger(bool p_isTrigger) { m_isTrigger = p_isTrigger; }
		bool IsTrigger() const { return m_isTrigger; }
		
		void SetOffset(const Vector3& p_offset) { m_offset = p_offset; }
		const Vector3& GetOffset() const { return m_offset; }

		AABB ComputeAABB() const;
		Rigidbody* GetBody() const { return m_body; }
	private:
		Rigidbody* m_body = nullptr;
		ShapeType m_type;

		SphereShape m_sphere;
		BoxShape m_box;

		Vector3 m_offset = Vector3(0.0f, 0.0f, 0.0f);
		bool m_isTrigger = false;
	};
}

#endif // !COLLIDER_HPP
