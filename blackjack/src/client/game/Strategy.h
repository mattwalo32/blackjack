#pragma once

#include <string>
#include <vector>
#include <functional>

#include "Card.h"
#include "GameConstants.h"
#include "utils/TimeUtils.h"
#include "../ConnectionListener.h"
#include "../../server/ConnectionConstants.h"
#include "../../server/utils/ConnectionUtils.h"
#include "../comm/WsMessage.h"


class Strategy {
public:
	typedef std::function<bool(WsMessage)> validationFunc;
	
	virtual void dealCard(Card card);
	virtual bool wantsToHit();
	void updateScore();
	
	void addToBalance(int amount);
	void removeFromBalance(int amount);
	void clearHand();
	
	void setName(std::string name);
	void addWin();
	int getCurrentBet();
	int getBalance();
	int getNumWins();
	int getHandValue();
	bool isBust();
	bool hasNaturalBlackjack();
	bool playerIsDealer();
	std::string getName();

protected:
	int balance;
	int currentBet;
	int currentHandScore;
	int numWins;
	bool busted;
	bool naturalBlackjack;
	bool isDealer;

	std::string name;
	std::vector<Card> currentHand;
	ConnectionListener* connection;
};
