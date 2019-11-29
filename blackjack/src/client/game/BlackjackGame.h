#pragma once

#include <vector>
#include <thread>
#include "Player.h"
#include "Deck.h"
#include "GameConstants.h"
#include "utils/TimeUtils.h"
#include "../ConnectionListener.h"

class BlackjackGame {

public:
	BlackjackGame(std::vector<Player> players, ConnectionListener* listener);
	void startGame();
	void resetGame();

	void addPlayer();
	void removePlayer();

private:
	Deck deck;
	std::vector<Player> players;
	Player* currentPlayer;
	ConnectionListener* connection;
	bool gameIsRunning;

	void placeBets();
	void dealCards();
	void waitForResponse();

};
