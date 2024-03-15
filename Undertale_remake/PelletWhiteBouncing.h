#pragma once
#include "PelletWhiteNonHoming.h"
#include "auxiliary.h"
#include "Timer.h"
class PelletWhiteBouncing :
    public PelletWhiteNonHoming
{
    uint64_t lifespan;
    Timer lifetime{};
    bool shouldExit = false;
public:
    PelletWhiteBouncing(Vector2 pos, float radius, float speed, Vector2 direction, uint64_t lifespan);
    virtual void Init() override;
    virtual void Update() override;
    //virtual bool ShouldDespawn() override;
};

