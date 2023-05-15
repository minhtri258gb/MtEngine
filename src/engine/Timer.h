#ifndef __MT_TIMER_H__
#define __MT_TIMER_H__

namespace mt {
namespace engine {

class Timer
{
public:

	// Variables
	static Timer ins;

	// Forwards
	Timer();
	~Timer();
	
	void init();
	void sleep();

	// Natives
	void setFPSLimit(int);
	int getFPS();
	float getTimePassed();

	void startCount();
	long long stopCount();

private:

	// Variables
	class TimerImpl;
	TimerImpl* impl;
};

}}

#endif
