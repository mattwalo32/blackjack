#pragma once

#include <vector>
#include <thread>
#include "Player.h"
#include "Deck.h"
#include "GameConstants.h"
#include "utils/TimeUtils.h"
#include "../ConnectionListener.h"
#include "../../server/ConnectionConstants.h"
#include "../../server/utils/ConnectionUtils.h"

typedef bool(*validationFunction)(std::string, Player* currentPlayer);

class BlackjackGame {
public:
	BlackjackGame(std::vector<Player*> players, ConnectionListener* listener);
	void startGame();
	void resetGame();

	void addPlayer();
	void removePlayer();

private:
	Deck deck;
	std::vector<Player*> players;
	Player* currentPlayer;
	ConnectionListener* connection;
	bool gameIsRunning;

	void placeBets();
	void dealCards();
	void takeTurns();
	std::string getPlayerResponse(std::vector<std::string> expectedPrefixes, validationFunction validate);

};
