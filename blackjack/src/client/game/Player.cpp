#include "Player.h"

using namespace GameConstants;

Player::Player(int startingBalance) {
	balance = startingBalance;
	currentHandScore = 0;
	busted = false;
	naturalBlackjack = false;
}

void Player::dealCard(Card card) {
	currentHand.push_back(card);
	
	int numAces = 0;
	int scoreBeforeAces = 0;
	int bestScore = 0;

	// Add up everything besides the aces
	for (Card card : currentHand) {
		if (card.getRank() == Card::ACE) {
			numAces++;
			continue;
		}

		scoreBeforeAces += card.getValue();
	}

	if (numAces == 0)
		bestScore = scoreBeforeAces;

	// Calculate best possible hand with aces
	for (int numHighStates = 0; numHighStates <= numAces; numHighStates++) {
		int sumOfAces = numHighStates * ACE_HIGH_VALUE + (numAces - numHighStates) * ACE_LOW_VALUE;
		int totalScore = scoreBeforeAces + sumOfAces;

		if (totalScore > bestScore && (totalScore <= WINNING_VALUE || bestScore == 0)) {
			bestScore = totalScore;
		}
	}

	busted = bestScore > WINNING_VALUE;
	naturalBlackjack = currentHand.size() == 2 && bestScore == WINNING_VALUE;
	currentHandScore = bestScore;
}

void Player::addToBalance(int amount) {
	balance += amount;
}

void Player::removeFromBalance(int amount) {
	balance -= amount;
}

void Player::clearHand() {
	currentHand.clear();
	currentBet = 0;
	busted = false;
}

void Player::setCurrentBet(int betAmount) {
	currentBet = betAmount;
}

int Player::getBalance() {
	return balance;
}

int Player::getCurrentBet() {
	return currentBet;
}

bool Player::isBust() {
	return busted;
}

bool Player::hasNaturalBlackjack() {
	return naturalBlackjack;
}

std::string Player::getName() {
	return name;
}