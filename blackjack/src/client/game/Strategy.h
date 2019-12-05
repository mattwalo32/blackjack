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

	float tableLocationX;
	float tableLocationY;
	float angle;

	virtual void dealCard(Card card) = 0;
	virtual bool wantsToHit() = 0;
	
	void clearHand();
	void setName(std::string name);
	void addWin();
	int getNumWins();
	int getHandValue();
	bool isBust();
	bool hasNaturalBlackjack();
	bool playerIsDealer();
	std::string getName();
	std::vector<std::string> getHandImgPaths();

protected:
	int currentHandScore;
	int numWins;
	bool busted;
	bool naturalBlackjack;
	bool isDealer;

	void updateScore();

	std::string name;
	std::vector<Card> currentHand;
	ConnectionListener* connection;
};
