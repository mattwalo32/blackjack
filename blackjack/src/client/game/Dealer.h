#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "Player.h"
#include "GameConstants.h"

class Dealer : public Player {
public:
	Dealer();
	void dealCard(Card card);
	bool wantsToHit();
};
