#include "Card.h"

Card::Card(Card::Rank rank, Card::Suit suit) {
	this->rank = rank;
	this->suit = suit;
}

int Card::getValue() {
	// Don't handle aces, that should be handled outside of class
	if (rank == Rank::JACK || rank == Rank::QUEEN || rank == Rank::KING)
		return 10;

	return rank + 1;
}

Card::Rank Card::getRank() {
	return rank;
}

Card::Suit Card::getSuit() {
	return suit;
}