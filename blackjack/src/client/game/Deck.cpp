#include "Deck.h"

Deck::Deck(int numDecks) {
	this->numDecks = numDecks;
	reset();
}

Deck::~Deck() {
	cards.clear();
}

void Deck::reset() {
	cards.clear();
	fillDeck();
	shuffleCards();
}

/*
 * Fills the deck with cards. These cards are unshuffled.
 */
void Deck::fillDeck() {
	for (int deckNum = 0; deckNum < numDecks; deckNum++) {
		for (int suitNum = 0; suitNum < Card::numSuits; suitNum++) {
			for (int rankNum = 0; rankNum < Card::numRanks; rankNum++) {
				Card::Suit suit = Card::Suit(suitNum);
				Card::Rank rank = Card::Rank(rankNum);
				Card* card = new Card(rank, suit);
				cards.push_back(card);
			}
		}
	}
}

/*
 * Randomly takes cards from the current deck and creates a
 * newly shuffled deck from this.
 */
void Deck::shuffleCards() {
	std::vector<Card*> unshuffledDeck = cards;
	std::vector<Card*> shuffledDeck;
	int numCards = unshuffledDeck.size();


	for (int i = 0; i < numCards; i++) {
		int cardsRemaining = unshuffledDeck.size();
		int cardIndex = rand() % cardsRemaining;

		shuffledDeck.push_back(unshuffledDeck.at(cardIndex));
		unshuffledDeck.erase(unshuffledDeck.begin() + cardIndex);
	}

	cards = shuffledDeck;
}

Card Deck::drawCard() {
	if (cards.size() > 0) {
		Card card = *cards.at(cards.size() - 1);
		cards.pop_back();
		return card;
	}

	reset();
	return drawCard();
}

int Deck::size() {
	return cards.size();
}