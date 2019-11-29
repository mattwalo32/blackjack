#pragma once

class Card {
public:
	enum Suit { DIAMONDS = 0, HEARTS, SPADES, CLUBS };
	enum Rank { 
		ACE = 0, 
		TWO, 
		THREE, 
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		NINE,
		TEN,
		JACK,
		QUEEN,
		KING 
	};

	static const int numSuits = 4;
	static const int numRanks = 13;
	static const int deckSize = numSuits * numRanks;

	Card(Rank rank, Suit suit);

	int getValue();
	Rank getRank();
	Suit getSuit();

private:
	Rank rank;
	Suit suit;
};
