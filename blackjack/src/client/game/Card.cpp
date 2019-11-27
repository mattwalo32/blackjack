#include "Card.h"

Card::Card(Card::Rank rank, Card::Suit suit) {
	this->rank = rank;
	this->suit = suit;
}

Card::Rank Card::getRank() {
	return rank;
}

Card::Suit Card::getSuit() {
	return suit;
}