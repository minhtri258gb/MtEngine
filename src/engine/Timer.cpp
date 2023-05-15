#define __MT_TIMER_CPP__

#include <chrono>

#include "common.h"
#include "Timer.h"

using namespace mt::engine;

class Timer::TimerImpl
{
public:
	long frameTimeLimit;
	long lastTime;
	float elapsedTime;

	std::chrono::_V2::system_clock::time_point startCount;
};

Timer Timer::ins;

Timer::Timer()
{
	// Implement
	impl = new TimerImpl;

	impl->frameTimeLimit = (long)(1000.0 / 60.0);
	impl->lastTime = 0;
	impl->elapsedTime = 0.0f;
}

Timer::~Timer()
{
	// Implement
	delete impl;
}

void Timer::init()
{
	impl->lastTime = clock();
}

void Timer::setFPSLimit(int value)
{
	impl->frameTimeLimit = (long)(1000.0 / value);
}

int Timer::getFPS()
{
    return (impl->elapsedTime != 0.0f) ? int(1.0f / impl->elapsedTime) : 0;
}

void Timer::sleep()
{
	long nextTime = impl->frameTimeLimit + impl->lastTime;
	while (clock() < nextTime) { } // Sleep
	long curTime = clock();
    impl->elapsedTime = (curTime - impl->lastTime) / 1000.0f;
    impl->lastTime = curTime;
}

float Timer::getTimePassed()
{
    return impl->elapsedTime;
}

void Timer::startCount()
{
	impl->startCount = std::chrono::high_resolution_clock::now();
}

long long Timer::stopCount()
{
	std::chrono::_V2::system_clock::time_point stop = std::chrono::high_resolution_clock::now();
	std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - impl->startCount);
	return duration.count();
}
