#include "Card.h"

Card::Card(Card::Rank rank, Card::Suit suit) {
	this->rank = rank;
	this->suit = suit;
}

/*
 * Calculates and returns the card code as a string. It's returned
 * as a string because it is often send to the server as a string. The
 * card code is as follows:
 * Codes 0, 1, 2, and 3 are the aces of diamonds, hearts, spades, and clubs.
 * Codes 4, 5, 6, and 7 are the 2's in the same order of suits and so on.
 */
std::string Card::getCode() {
	int code = rank * numSuits + suit;
	return std::to_string(code);
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