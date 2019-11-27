#include "Deck.h"

Deck::Deck() {
	for (int i = 0; i < Card::numSuits; i++) {
		for (int j = 0; j < Card::numRanks; j++) {
			Card::Suit suit = Card::Suit(i);
			Card::Rank rank = Card::Rank(j);
			Card* card = new Card(rank, suit);
			cards.push_back(card);
		}
	}
}
Deck::~Deck() {
	cards.clear();
}

void Deck::shuffleCards() {
	std::vector<Card*> unshuffledDeck = cards;
	std::vector<Card*> shuffledDeck;
	
	for (int i = 0; i < Card::deckSize; i++) {
		int cardsRemaining = unshuffledDeck.size();
		int cardIndex = rand() % cardsRemaining;

		shuffledDeck.push_back(unshuffledDeck.at(cardIndex));
		unshuffledDeck.erase(unshuffledDeck.begin() + cardIndex);
	}

	cards = shuffledDeck;
}