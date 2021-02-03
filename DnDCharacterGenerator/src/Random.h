#pragma once

#include <random>

class Random
{
public:
	// Seed the random engine
	static void Init()
	{
		s_RandomEngine.seed(std::random_device()());
	}

	// Return a random (unsigned) integer between min and max
	static int Int(int min, int max)
	{
		return (int)s_Distribution(s_RandomEngine, std::uniform_int_distribution<uint64_t>::param_type(min, max));
	}

	// Return the sum of n random integers between min and max
	static int IntSum(int min, int max, int n)
	{
		int sum = 0;
		for (int i = 0; i < n; i++)
			sum += Random::Int(min, max);

		return sum;
	}

	// Return a random size_t value between min and max
	static size_t Index(size_t min, size_t max)
	{
		return s_Distribution(s_RandomEngine, std::uniform_int_distribution<size_t>::param_type(min, max));
	}

	static std::mt19937 GetEngine()
	{
		return s_RandomEngine;
	}

private:
	inline static std::mt19937 s_RandomEngine;
	inline static std::uniform_int_distribution<uint64_t> s_Distribution;
};