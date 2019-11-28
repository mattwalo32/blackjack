#pragma once

#include "Card.h"
#include <vector>
#include <cstdlib>

class Deck {
public:
	Deck(int numDecks);
	~Deck();

	void reset();
	Card drawCard();

private:
	int numDecks;
	void fillDeck();
	void shuffleCards();
	std::vector<Card*> cards;

};
