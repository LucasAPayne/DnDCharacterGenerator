#pragma once

#include <random>

class Random
{
public:
	// Seed the random engine
	static void init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	// Return a random integer between min and max
	static int drawNumber(unsigned int min, unsigned int max)
	{
		return s_Distribution(s_RandomEngine, std::uniform_int_distribution<unsigned>::param_type(min, max));
	}

	static std::mt19937 getEngine()
	{
		return s_RandomEngine;
	}

private:
	inline static std::mt19937 s_RandomEngine;
	inline static std::uniform_int_distribution<std::mt19937::result_type> s_Distribution;
};