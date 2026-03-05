#ifndef NARROWPHASE_HPP
#define NARROWPHASE_HPP
#include <vector>
#include "Broadphase.hpp"
#include "Contact.hpp"

namespace physics
{
	class Narrowphase
	{
	public:
		static void GenerateContacts(const std::vector<CollisionPair>& p_collisionPairs, std::vector<Contact>& p_outContacts);
	};
}

#endif // !NARROWPHASE_HPP

