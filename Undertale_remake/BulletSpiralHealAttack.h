#pragma once
#include "Attack.h"
#include "BulletSpiralAttack.h"

class BulletSpiralHealAttack :
    public Attack
{
    BulletSpiralAttack spiral;
    PeriodicTimer healFreq;
public:
    BulletSpiralHealAttack(uint64_t duration);
    void Setup() override;
    void Update() override;
};

