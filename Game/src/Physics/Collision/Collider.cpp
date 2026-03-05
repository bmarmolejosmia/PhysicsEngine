#include "Collider.hpp"
#include "..\Rigidbody\Rigidbody.hpp"

namespace physics
{
	Collider::Collider(Rigidbody* p_body, ShapeType p_type) : m_body(p_body), m_type(p_type)
	{

	}

	AABB Collider::ComputeAABB() const
	{
		Vector3 center(0.0f, 0.0f, 0.0f);

		if (m_body)
		{
			center = m_body->GetPosition();
		}

		center += m_offset;

		switch (m_type)
		{
			case ShapeType::Sphere:
			{
				const float r = m_sphere.radius;
				const Vector3 extent(r, r, r);
				return AABB(center - extent, center + extent);
			}
			case ShapeType::Box:
			{
				const Vector3& half = m_box.halfSize;
				return AABB(center - half, center + half);
			}

			default:
				return AABB(center, center);
		}
	}
}