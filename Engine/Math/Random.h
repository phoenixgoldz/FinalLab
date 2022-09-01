#pragma once
#include <random>

namespace phoenix
{
	inline void seedRandom(int seed) { srand(seed); }

	inline int random() { return rand(); }
	inline int random(int max) { return rand() % max; }
	inline int random(int min, int max) { return min + rand() % ((max - min) + 1); }

	inline float randomf() { return rand() / (float)RAND_MAX; }
	inline float randomf(float max) { return randomf() * max; }
	inline float randomf(float min, float max) { return min + randomf(max - min); }


}
