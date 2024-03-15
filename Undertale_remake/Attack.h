#pragma once
#include "auxiliary.h"
#include "Player.h"
#include "Battlefield.h"

class Attack
{
protected:
	uint64_t duration;
	Player* player;
	Battlefield* battlefield;
	
public:
	Attack(uint64_t duration);
	uint64_t GetDuration();
	void SetPlayer(Player* player);
	void SetBattlefield(Battlefield* battlefield);
	virtual void Setup() = 0;
	virtual void Update() = 0;
	virtual ~Attack() {}
};

