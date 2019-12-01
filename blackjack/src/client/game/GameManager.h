#pragma once

#include "Player.h"
#include "BlackjackGame.h"
#include "../comm/WsMessage.h"
#include <string>

class GameManager {
public:
	~GameManager();
	void init();
	void openLobby();
	void startGame();
	void updatePlayerName(WsMessage msg);
	void addPlayer(WsMessage msg);

	std::vector<Player*> getPlayers();

private:
	BlackjackGame* game;
	std::vector<Player*> players;
	ConnectionListener connListener;
};
