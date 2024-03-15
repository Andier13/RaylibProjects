#pragma once
#include "Attack.h"
#include "Timer.h"
#include "auxiliary.h"

class BulletSpiralAttack :
    public Attack
{
    PeriodicTimer attackFreq;
    int count;
    float phase;
    float deltaPhase;
    Vector2 source;

public:
    BulletSpiralAttack(uint64_t duration);
    void SetSource(Vector2 source);
    void Setup() override;
    void Update() override;
};

