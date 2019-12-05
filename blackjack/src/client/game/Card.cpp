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
	std::string codeStr = std::to_string(code);

	if (codeStr.length() == 1)
		codeStr = "0" + codeStr;

	return codeStr;
}

int Card::getValue() {
	// Don't handle aces, that should be handled outside of class
	if (rank == Rank::JACK || rank == Rank::QUEEN || rank == Rank::KING)
		return 10;

	return rank + 1;

	throw new std::invalid_argument("Get value cannot be invoked on Aces");
}

Card::Rank Card::getRank() {
	return rank;
}

Card::Suit Card::getSuit() {
	return suit;
}

std::string Card::getFilename() {
	const int code = std::stoi(getCode());

	switch (code) {
		case 0: return "AD";
		case 1: return "AH";
		case 2: return "AS";
		case 3: return "AC";

		case 4: return "2D";
		case 5: return "2H";
		case 6: return "2S";
		case 7: return "2C";

		case 8: return "3D";
		case 9: return "3H";
		case 10: return "3S";
		case 11: return "3C";

		case 12: return "4D";
		case 13: return "4H";
		case 14: return "4S";
		case 15: return "4C";

		case 16: return "5D";
		case 17: return "5H";
		case 18: return "5S";
		case 19: return "5C";

		case 20: return "6D";
		case 21: return "6H";
		case 22: return "6S";
		case 23: return "6C";

		case 24: return "7D";
		case 25: return "7H";
		case 26: return "7S";
		case 27: return "7C";

		case 28: return "8D";
		case 29: return "8H";
		case 30: return "8S";
		case 31: return "8C";

		case 32: return "9D";
		case 33: return "9H";
		case 34: return "9S";
		case 35: return "9C";

		case 36: return "10D";
		case 37: return "10H";
		case 38: return "10S";
		case 39: return "10C";

		case 40: return "JD";
		case 41: return "JH";
		case 42: return "JS";
		case 43: return "JC";

		case 44: return "QD";
		case 45: return "QH";
		case 46: return "QS";
		case 47: return "QC";

		case 48: return "KD";
		case 49: return "KH";
		case 50: return "KS";
		default:
		case 51: return "KC";
	}
}