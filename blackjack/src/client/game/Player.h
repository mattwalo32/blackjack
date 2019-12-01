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


class Player {
public:
	typedef std::function<bool(WsMessage)> validationFunc;
	Player(ConnectionListener* listener, std::string name, int startingBalance);
	
	void dealCard(Card card);
	
	void updateScore();
	bool wantsToHit();
	
	void addToBalance(int amount);
	void removeFromBalance(int amount);
	void clearHand();
	
	void setCurrentBet(int betAmount);
	void setName(std::string name);
	int getCurrentBet();
	int getBalance();
	bool isBust();
	bool hasNaturalBlackjack();
	bool playerIsDealer();
	std::string getName();

protected:
	int balance;
	int currentBet;
	int currentHandScore;
	bool busted;
	bool naturalBlackjack;
	bool isDealer;

	std::string name;
	std::vector<Card> currentHand;
	ConnectionListener* connection;

	WsMessage Player::getPlayerResponse(std::vector<std::string> expectedPrefixes, validationFunc isValid);

};
