#pragma once
#include "Attack.h"
class PauseAttack :
    public Attack
{
public:
    PauseAttack(uint64_t duration);
    void Setup() override;
    void Update() override;
};

