#ifndef BROADPHASE_HPP
#define BROADPHASE_HPP
#include <vector>
#include <utility>

namespace physics
{
	class Collider;

	using CollisionPair = std::pair<Collider*, Collider*>;

	class Broadphase
	{
	public:
		static void ComputeCollisionPairs(const std::vector<Collider*>& p_colliders, std::vector<CollisionPair>& p_outCollisionPairs);
	};
}

#endif // !BROADPHASE_HPP
