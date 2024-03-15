#pragma once
#include "Attack.h"
#include "Timer.h"
class NewAttack1 :
    public Attack
{
    PeriodicTimer attackFreq;
    bool first;
public:
    NewAttack1(uint64_t duration);
    void Setup() override;
    void Update() override;
};

