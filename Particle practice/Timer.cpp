#include "Timer.h"

PeriodicTimer::PeriodicTimer(uint64_t interval) : startTime(timeSinceEpochMillisec()), prevTime(startTime), interval(interval)
{
}

PeriodicTimer::PeriodicTimer() : startTime(0), prevTime(startTime), interval(0)
{
}

void PeriodicTimer::Set(uint64_t interval)
{
	startTime = timeSinceEpochMillisec();
	prevTime = startTime;
	this->interval = interval;
}

void PeriodicTimer::Reset()
{
	if (startTime == 0)
		return;
	startTime = timeSinceEpochMillisec();
	prevTime = startTime;
}

bool PeriodicTimer::operator()()
{
	uint64_t currentTime = timeSinceEpochMillisec();
	uint64_t prevDt = prevTime - startTime;
	uint64_t currentDt = currentTime - startTime;

	prevTime = currentTime;
	return (currentDt / interval == prevDt / interval + 1);
}

Timer::Timer(uint64_t interval) : 
	startTime(timeSinceEpochMillisec()), prevTime(startTime), interval(interval), hasFinished(false)
{
}

Timer::Timer() : startTime(0), prevTime(startTime), interval(0), hasFinished(true)
{
}

void Timer::Set(uint64_t interval)
{
	startTime = timeSinceEpochMillisec();
	prevTime = startTime;
	this->interval = interval;
	hasFinished = false;

}

void Timer::Reset()
{
	if (startTime == 0)
		return;
	startTime = timeSinceEpochMillisec();
	prevTime = startTime;
	hasFinished = false;
}

bool Timer::operator()()
{
	if (hasFinished)
		return false;
	uint64_t currentTime = timeSinceEpochMillisec();
	uint64_t prevDt = prevTime - startTime;
	uint64_t currentDt = currentTime - startTime;

	prevTime = currentTime;
	hasFinished = (currentDt / interval == prevDt / interval + 1);
	return hasFinished;
}

TimerSequenceIntervals::TimerSequenceIntervals(std::initializer_list<uint64_t> v) :
	startTime(timeSinceEpochMillisec()), prevTime(startTime), intervals(v), hasFinished(false),
	totalInterval(*v.begin()), counter(0)
{

}

TimerSequenceIntervals::TimerSequenceIntervals() :
	startTime(0), prevTime(startTime), intervals(), hasFinished(true),
	totalInterval(0), counter(0)
{
}

void TimerSequenceIntervals::Set(std::initializer_list<uint64_t> v)
{
	startTime = timeSinceEpochMillisec();
	prevTime = startTime;
	intervals = v;
	hasFinished = false;
	totalInterval = *intervals.begin();
	counter = 0;
}

void TimerSequenceIntervals::Reset()
{
	startTime = timeSinceEpochMillisec();
	prevTime = startTime;
	hasFinished = false;
	totalInterval = *intervals.begin();
	counter = 0;
}

bool TimerSequenceIntervals::operator()()
{
	if (hasFinished)
		return false;
	uint64_t currentTime = timeSinceEpochMillisec();
	uint64_t prevDt = prevTime - startTime;
	uint64_t currentDt = currentTime - startTime;

	prevTime = currentTime;
	bool rez = (currentDt / totalInterval == prevDt / totalInterval + 1);
	if (rez)
	{
		if (counter + 1 < intervals.size())
			totalInterval += intervals[counter + 1];
		counter++;
	}

	if (counter == intervals.size())
	{
		hasFinished = true;
		//intervals.clear();
	}
	return rez;
}

int TimerSequenceIntervals::GetCounter()
{
	return counter;
}
