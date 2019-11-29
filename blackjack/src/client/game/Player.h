#pragma once

#include <string>
#include <vector>

#include "Card.h"
#include "GameConstants.h"

class Player {
public:
	Player(int startingBalance);
	void dealCard(Card card);
	void addToBalance(int amount);
	void removeFromBalance(int amount);
	void clearHand();
	
	void setCurrentBet(int betAmount);
	int getCurrentBet();
	int getBalance();
	bool isBust();
	bool hasNaturalBlackjack();
	std::string getName();

private:
	int balance;
	int currentBet;
	int currentHandScore;
	bool busted;
	bool naturalBlackjack;

	std::string name;
	std::vector<Card> currentHand;
};
