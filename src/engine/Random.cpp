#define __MT_RANDOM_CPP__

#include <ctime>
#include <random>

#include "common.h"
#include "Random.h"

#include "engine/utils/GeneralUtils.h"

using namespace std;
using namespace mt::engine;

class Random::RandomImpl
{
public:
	mt19937 rd;
};

Random Random::ins;

Random::Random()
{
	// Implement
	impl = new RandomImpl;

  // Component
	impl-> rd = std::mt19937(time(NULL));
}

Random::~Random()
{
	// Implement
	delete impl;
}

bool Random::probability(unsigned int n)
{
	return (impl->rd() % 100 < n);
}

unsigned int Random::rand(unsigned int n)
{
	return impl->rd() % n;
}

int Random::range(int d, int c)
{
	if (d > c) GeneralUtils::swap(d,c);
	return impl->rd()%(c-d+1)+d;
}

float Random::rangeF(float d, float c)
{
	return (float)range(((int)d * 1000), ((int)c * 1000)) * 0.001f;
}
