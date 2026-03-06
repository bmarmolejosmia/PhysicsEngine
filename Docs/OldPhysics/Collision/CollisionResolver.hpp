#ifndef COLLISIONRESOLVER_HPP
#define COLLISIONRESOLVER_HPP
#include <vector>

namespace physics
{
	struct Contact;

	class CollisionResolver
	{
	public:
		static void ResolveContacts(std::vector<Contact>& p_contacts);
	};
}

#endif // !COLLISIONRESOLVER_HPP
