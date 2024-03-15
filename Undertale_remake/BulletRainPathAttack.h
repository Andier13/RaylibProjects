#pragma once
#include "Attack.h"
#include "Timer.h"

class BulletRainPathAttack :
    public Attack
{
    PeriodicTimer attackFreq;
    uint64_t interval;
    int size;
    int count;
    int gapCount;
    int gapStart;
    int maxDeviation;

public:
    BulletRainPathAttack(int count);
    void Setup() override;
    void Update() override;
};

