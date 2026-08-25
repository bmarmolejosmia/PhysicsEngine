#ifndef SIMULATION_H
#define SIMULATION_H

#include "LifeStats.h"
#include <vector>

namespace game
{
	class Simulation
	{
	public:
		void RegisterLife(LifeStats* p_lifeStats);
		void UnregisterLife(LifeStats* p_lifeStats);
		void TickAll(float p_deltaTime);

		float TimeScale = 1.0f; // Default time scale is 1.0 (real-time)

	private:
		std::vector<LifeStats*> m_activeLives;
	};
}

#endif // !SIMULATION_H

