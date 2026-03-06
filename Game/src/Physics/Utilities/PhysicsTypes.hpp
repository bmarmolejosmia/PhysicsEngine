#ifndef PHYSICSTYPES_HPP
#define PHYSICSTYPES_HPP
#include <vector3d.h>
#include <quaternion.h>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <utility>

namespace physics
{
	using Vector3 = irr::core::vector3df;
	using Quat = irr::core::quaternion;

	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T, typename ... Args>
	inline Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	enum class PhysicsObjectState : uint8_t
	{
		Active,
		Inactive,
		Destroyed
	};

	struct PhysicsObjectLocation
	{
		PhysicsObjectState State = PhysicsObjectState::Active;
		std::size_t Index = 0;
	};
}
#endif // !PHYSICSTYPES_HPP
