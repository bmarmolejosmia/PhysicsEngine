#include "Broadphase.hpp"
#include "Collider.hpp"
#include "AABB.hpp"

namespace physics
{
    void Broadphase::ComputeCollisionPairs(const std::vector<Collider*>& p_colliders, std::vector<CollisionPair>& p_outCollisionPairs)
    {
        p_outCollisionPairs.clear();

        const size_t colliderCount = p_colliders.size();

        for (size_t firstIndex = 0; firstIndex < colliderCount; ++firstIndex)
        {
            Collider* firstCollider = p_colliders[firstIndex];
            
            if (!firstCollider)
            {
                continue;
            }

            const AABB firstAABB = firstCollider->ComputeAABB();

            for (size_t secondIndex = firstIndex + 1; secondIndex < colliderCount; ++secondIndex)
            {
                Collider* secondCollider = p_colliders[secondIndex];

                if (!secondCollider)
                {
                    continue;
                }

                const AABB secondAABB = secondCollider->ComputeAABB();

                if (firstAABB.Overlaps(secondAABB))
                {
                    p_outCollisionPairs.emplace_back(firstCollider, secondCollider);
                }
            }
        }
    }
}