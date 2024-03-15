#pragma once
#include "Attack.h"
#include "HandPuppet.h"
#include "Timer.h"
#include "SecondOrderDynamics.h"

class HandSwipesAttack :
	public Attack
{
	HandPuppet* hand[2];
	bool which = false;
	uint64_t startTime = 0;
	TimerSequenceIntervals sequence{};
	Vector2 target[2]{};
	SecondOrderDynamics swipe0{2, 0.8, -3};
	SecondOrderDynamics swipe1{2, 0.8, -3};

public:
	HandSwipesAttack();
	void Setup() override;
	void Update() override;
};

