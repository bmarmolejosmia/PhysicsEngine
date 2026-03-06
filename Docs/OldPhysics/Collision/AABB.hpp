#ifndef AABB_HPP
#define AABB_HPP
#include "..\Utilities\PhysicsTypes.hpp"
#include <algorithm>

namespace physics
{
	struct AABB
	{
		Vector3 min;
		Vector3 max;

		AABB() : min(0.0f, 0.0f, 0.0f), max(0.0f, 0.0f, 0.0f)
		{
		}

		AABB(const Vector3& p_minPoint, const Vector3& p_maxPoint) : min(p_minPoint), max(p_maxPoint)
		{
		}

		void ExpandToInclude(const AABB& p_other)
		{
			min.X = std::min(min.X, p_other.min.X);
			min.Y = std::min(min.Y, p_other.min.Y);
			min.Z = std::min(min.Z, p_other.min.Z);

			max.X = std::max(max.X, p_other.max.X);
			max.Y = std::max(max.Y, p_other.max.Y);
			max.Z = std::max(max.Z, p_other.max.Z);
		}

		bool Overlaps(const AABB& p_other) const
		{
			if (max.X < p_other.min.X || min.X > p_other.max.X) { return false; }
			if (max.Y < p_other.min.Y || min.Y > p_other.max.Y) { return false; }
			if (max.Z < p_other.min.Z || min.Z > p_other.max.Z) { return false; }
			
			return true;
		}

		Vector3 Center() const
		{
			return (min + max) * 0.5f;
		}

		Vector3 HalfSize() const
		{
			return (max - min) * 0.5f;
		}
	};
}

#endif // !AABB_HPP

