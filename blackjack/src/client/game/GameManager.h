#pragma once

#include "Player.h"
#include "BlackjackGame.h"
#include "../comm/WsMessage.h"
#include "Strategy.h"
#include <string>

class GameManager {
public:
	~GameManager();
	void init();
	void startGame();
	void updatePlayerName(WsMessage msg);
	void addPlayer(WsMessage msg);
	BlackjackGame* getRunningGame();

	std::vector<Strategy*> getPlayers();

private:
	BlackjackGame* game;
	std::vector<Strategy*> players;
	ConnectionListener connListener;
};
