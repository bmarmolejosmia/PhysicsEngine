#ifndef LIFESTATS_H
#define LIFESTATS_H

#include <string>
#include <vector>

namespace game
{
	struct Motive
	{
		float Value;
		float MaxValue;
		float DecayRate;

		Motive(float p_max = 100.0f, float p_decayRate = 1.0f)
			: Value(p_max), MaxValue(p_max), DecayRate(p_decayRate) 
		{
		}

		void Tick(float p_baseTimeAmount)
		{
			Value -= p_baseTimeAmount * DecayRate;

			if (Value < 0.0f) Value = 0.0f;
			if (Value > MaxValue) Value = MaxValue;
		}
	};

	struct LifeStats
	{
		Motive Hunger;
		Motive Energy;
		Motive Bladder;
		Motive Hygiene;
		Motive Social;
		Motive Fun;

		std::vector<std::string> Traits;

		LifeStats()
			: Hunger(100.0f, 1.5f), Energy(100.0f, 0.8f), Bladder(100.0f, 2.0f),
			Hygiene(100.0f, 1.0f), Social(100.0f, 0.5f), Fun(100.0f, 1.0f)
		{
		}

		void Tick(float p_deltaTime)
		{
			float baseDecay = 0.5f * p_deltaTime; // Adjust decay rate as needed

			Hunger.Tick(baseDecay);
			Energy.Tick(baseDecay);
			Bladder.Tick(baseDecay);
			Hygiene.Tick(baseDecay);
			Social.Tick(baseDecay);
			Fun.Tick(baseDecay);
		}
	};
}

#endif // !LIFESTATS_H

