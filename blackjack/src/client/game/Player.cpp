#include "Player.h"

Player::Player(int startingBalance) {
	balance = startingBalance;
	busted = false;
}

void Player::dealCard(Card card) {
	currentHand.push_back(card);
	
	//TODO: Check if bust

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