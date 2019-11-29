#pragma once

#include "Card.h"
#include "GameConstants.h"
#include <vector>
#include <cstdlib>

class Deck {
public:
	Deck(int numDecks = GameConstants::DEFAULT_NUM_DECKS);
	~Deck();

	void reset();
	Card drawCard();

private:
	int numDecks;
	void fillDeck();
	void shuffleCards();
	std::vector<Card*> cards;

};
