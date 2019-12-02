#pragma once

#include <string>

#include "Strategy.h"
/*#include "GameConstants.h"
#include <vector>
#include "utils/TimeUtils.h"
#include <functional>
#include "Card.h"
#include "../ConnectionListener.h"
#include "../../server/ConnectionConstants.h"
#include "../../server/utils/ConnectionUtils.h"
#include "../comm/WsMessage.h"*/


class Player : public Strategy {
public:
	Player(ConnectionListener* listener, std::string name, int startingBalance);
	void dealCard(Card card);
	bool wantsToHit();
	
private:
	WsMessage Player::getPlayerResponse(std::vector<std::string> expectedPrefixes, validationFunc isValid);

};
