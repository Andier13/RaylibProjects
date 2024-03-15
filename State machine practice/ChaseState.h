#pragma once
#include "EntityState.h"
class ChaseState :
    public EntityState
{
    Vector2 direction = { 0, 0 };
    float speed = 100;

public:
    void OnEnter() override;
    void Update() override;

    ChaseState(Entity& entity);
};

