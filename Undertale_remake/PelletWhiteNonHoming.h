#pragma once
#include "PelletWhite.h"

class PelletWhiteNonHoming :
    public PelletWhite
{
    Vector2 direction;
public:
    PelletWhiteNonHoming(Vector2 pos, float radius, float speed, Vector2 direction);
    virtual void Init();
};

