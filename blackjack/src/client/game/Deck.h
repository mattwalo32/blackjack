#pragma once

#include "Card.h"
#include <vector>
#include <cstdlib>

class Deck {
public:
	Deck();
	~Deck();
	void shuffleCards();

private:
	std::vector<Card*> cards;

};
