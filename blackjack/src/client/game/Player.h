#pragma once

#include <string>
#include <vector>

#include "Card.h"

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

private:
	int balance;
	int currentBet;
	bool busted;

	std::string name;
	std::vector<Card> currentHand;
};
