#pragma once
#include "auxiliary.h"
#include <initializer_list>

class PeriodicTimer
{
	uint64_t startTime;
	uint64_t prevTime;
	uint64_t interval;
public:
	PeriodicTimer(uint64_t interval);
	PeriodicTimer();
	void Set(uint64_t interval);
	void Reset();
	bool operator()();
};

class Timer
{
	uint64_t startTime;
	uint64_t prevTime;
	uint64_t interval;
	bool hasFinished;
public:
	Timer(uint64_t interval);
	Timer();
	void Set(uint64_t interval);
	void Reset();
	bool operator()();
};

class TimerSequenceIntervals
{
	uint64_t startTime;
	uint64_t prevTime;
	std::vector<uint64_t> intervals;
	uint64_t totalInterval;
	uint64_t counter;
	bool hasFinished;
public:
	TimerSequenceIntervals(std::initializer_list<uint64_t> v);
	TimerSequenceIntervals();
	void Set(std::initializer_list<uint64_t> v);
	void Reset();
	bool operator()();
	int GetCounter();
};
