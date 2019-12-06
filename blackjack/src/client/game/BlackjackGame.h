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

class BlackjackGame {
public:
	BlackjackGame(std::vector<Strategy*> players, ConnectionListener* listener);
	void startGame();
	void resetGame();
	void addPlayer();
	void removePlayer();


	std::vector<Strategy*> getPlayers();

private:
	Deck deck;
	std::vector<Strategy*> players;
	Strategy* currentPlayer;
	Strategy* dealer;
	ConnectionListener* connection;
	bool gameIsRunning;

	void dealCards();
	void takeTurns();
	void updateWinners(std::vector<Strategy*> winners);
	void clearHand();
	std::vector<Strategy*> getWinners(bool turnsAreFinished);
};
