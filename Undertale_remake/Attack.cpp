#include "Attack.h"

Attack::Attack(uint64_t duration) : 
	duration(duration), player(nullptr), battlefield(nullptr)
{
}

uint64_t Attack::GetDuration()
{
	return duration;
}

void Attack::SetPlayer(Player* player)
{
	this->player = player;
}

void Attack::SetBattlefield(Battlefield* battlefield)
{
	this->battlefield = battlefield;
}
