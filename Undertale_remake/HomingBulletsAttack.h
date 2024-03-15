#pragma once
#include "Attack.h"
#include "Timer.h"

class HomingBulletsAttack :
    public Attack
{
    PeriodicTimer attackFreq;
public:
    HomingBulletsAttack(uint64_t duration);
    void Setup() override;
    void Update() override;
};

