#pragma once
#include "Attack.h"
class ResizeBattlefieldAttack :
    public Attack
{
    Vector2 originalSize;
    Vector2 finalSize;
    uint64_t startTime;
public:
    ResizeBattlefieldAttack(uint64_t duration);
    void SetFinalSize(Vector2 finalSize);
    void Setup() override;
    void Update() override;
};

