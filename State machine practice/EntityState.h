#pragma once
#include "State.h"
#include "auxiliary.h"
#include "Entity.h"

class EntityState :
    public State
{
protected:
    Entity& entity;
public:
    Vector2 velocity = { 0, 0 };

    virtual void OnEnter() override;
    virtual void OnExit() override;
    virtual void Update() override;
    EntityState(Entity& entity, const Vector2& velocity);
    EntityState(Entity& entity);
};

