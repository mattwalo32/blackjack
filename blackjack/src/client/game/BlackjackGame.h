#pragma once

#include <vector>
#include <thread>
#include <atomic>
#include "Player.h"
#include "Deck.h"
#include "GameConstants.h"
#include "utils/TimeUtils.h"
#include "../ConnectionListener.h"
#include "../../server/ConnectionConstants.h"
#include "../../server/utils/ConnectionUtils.h"

class BlackjackGame {
public:
	BlackjackGame(const atomic<bool>* gameRunning, std::vector<Strategy*> players, ConnectionListener* listener);
	~BlackjackGame();
	void startGame();
	bool isGameRunning();
	void stopGame();
	std::vector<Strategy*> getPlayers();

private:
	Deck deck;
	std::vector<Strategy*> players;
	Strategy* currentPlayer;
	Strategy* dealer;
	ConnectionListener* connection;
	const std::atomic<bool>* gameIsRunning;

	void dealCards();
	void takeTurns();
	void updateWinners(std::vector<Strategy*> winners);
	void clearHand();
	std::vector<Strategy*> getWinners(bool turnsAreFinished);
};
