#pragma once
#include "Attack.h"
#include "Timer.h"

class BulletWallAttack :
    public Attack
{
    PeriodicTimer attackFreq;
    bool colorFlag;
public:
    BulletWallAttack(uint64_t duration);
    void Setup() override;
    void Update() override;
};

