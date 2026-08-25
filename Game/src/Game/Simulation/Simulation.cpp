#include "Simulation.h"
#include <algorithm>

namespace game
{
	void Simulation::RegisterLife(LifeStats* p_lifeStats)
	{
		if (p_lifeStats && std::find(m_activeLives.begin(), m_activeLives.end(), p_lifeStats) == m_activeLives.end())
		{
			m_activeLives.push_back(p_lifeStats);
		}
	}
	void Simulation::UnregisterLife(LifeStats* p_lifeStats)
	{
		auto it = std::remove(m_activeLives.begin(), m_activeLives.end(), p_lifeStats);
		if (it != m_activeLives.end())
		{
			m_activeLives.erase(it, m_activeLives.end());
		}
	}
	void Simulation::TickAll(float p_deltaTime)
	{
		float scaledDeltaTime = p_deltaTime * TimeScale;
		for (LifeStats* life : m_activeLives)
		{
			if (life)
			{
				life->Tick(scaledDeltaTime);
			}
		}
	}
}