#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "Player.h"
#include "GameConstants.h"
#include "Strategy.h"

class Dealer : public Strategy {
public:
	Dealer();
	void dealCard(Card card);
	bool wantsToHit();
};
