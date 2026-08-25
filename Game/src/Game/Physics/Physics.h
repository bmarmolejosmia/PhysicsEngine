#ifndef PHYSICS_H
#define PHYSICS_H

#include <irrlicht.h>
#include <vector>

namespace game
{
	class Physics
	{
	public:
		void AddStaticCollider(const irr::core::aabbox3df& p_box);
		irr::core::vector3df MoveKinematic(irr::core::aabbox3df p_playerBox, irr::core::vector3df p_velocity);

		void ClearColliders();
	private:
		std::vector<irr::core::aabbox3df> m_staticColliders;
	};
}

#endif // !PHYSICS_H

