#include "Dealer.h"

using namespace GameConstants;

Dealer::Dealer() {
	this->name = "Dealer";
	balance = 0;
	currentHandScore = 0;
	busted = false;
	naturalBlackjack = false;
	connection = nullptr;
	isDealer = true;
}

/*
 * Adds the card to the players hand and updates score.
 */
void Dealer::dealCard(Card card) {
	currentHand.push_back(card);
	updateScore();
}

bool Dealer::wantsToHit() {
	return currentHandScore < GameConstants::DEALER_HIT_AMOUNT;
}