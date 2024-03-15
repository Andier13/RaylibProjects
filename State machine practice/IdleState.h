#pragma once
#include "EntityState.h"
class IdleState :
    public EntityState
{
    uint64_t duration = 2000;
    uint64_t startTime = 0;
    Vector2 direction = { 0, 0 };
    float speed = 100;

public:
    void OnEnter() override;
    void Update() override;

    IdleState(Entity& entity);
};

