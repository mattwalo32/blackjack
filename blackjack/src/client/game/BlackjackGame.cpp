#include "BlackjackGame.h"

using namespace TimeUtils;

BlackjackGame::BlackjackGame(std::vector<Strategy*> players, ConnectionListener* listener) {
	this->players = players;
	connection = listener;
	gameIsRunning = false;

	int tableLocationOffset = GameConstants::MIDDLE_TABLE_INDEX - ((players.size() - 1) / 2);

	for (int i = 0; i < players.size(); i++) {
		Strategy* strategy = players.at(i);

		int tableLocIndex = i + tableLocationOffset;

		if (strategy->playerIsDealer()) {
			strategy->tableLocationX = GameConstants::DEALER_LOCATION[0];
			strategy->tableLocationY = GameConstants::DEALER_LOCATION[1];
			strategy->angle = GameConstants::DEALER_LOCATION[2];
			dealer = strategy;
		} else {
			strategy->tableLocationX = GameConstants::TABLE_LOCATIONS[tableLocIndex][0];
			strategy->tableLocationY = GameConstants::TABLE_LOCATIONS[tableLocIndex][1];
			strategy->angle = GameConstants::TABLE_LOCATIONS[tableLocIndex][2];
		}	
	}
}

BlackjackGame::~BlackjackGame() {
	delete currentPlayer;
	delete dealer;
}

/*
 * Runs through a game of blackjack until there are no players left. This
 * method should be run on another thread or the UI will be blocked.
 */
void BlackjackGame::startGame() {
	gameIsRunning = true;
	std::vector<Strategy*> winners;

	while (gameIsRunning) {
		dealCards();
		winners = getWinners(false);

		if (winners.size() == 0) {
			takeTurns();
			winners = getWinners(true);
		}

		updateWinners(winners);
		std::this_thread::sleep_for(std::chrono::seconds(GameConstants::ROUND_RESET_DELAY_SEC));
		winners.clear();
		clearHand();
	}
}

void BlackjackGame::dealCards() {
	for (int cardNum = 0; cardNum < GameConstants::NUM_STARTING_CARDS; cardNum++) {
		for (Strategy* player : players) {
			Card card = deck.drawCard();
			player->dealCard(card);
		}
	}
}

/*
 * See if each player wants to hit or stay. May freeze thread while waiting
 * for response.
 */
void BlackjackGame::takeTurns() {
	for (Strategy* player : players) {
		while (!player->isBust() && player->wantsToHit()) {
			player->dealCard(deck.drawCard());
		}

		connection->sendMessage(ConnectionConstants::CMD_TURNEND + player->getName());
	}
}

void BlackjackGame::clearHand() {
	for (Strategy* player : players)
		player->clearHand();
}

void BlackjackGame::updateWinners(std::vector<Strategy*> winners) {
	if (winners.empty()) {
		connection->sendMessage(ConnectionConstants::CMD_BROADCAST_WINNER + "No one");
		return;
	}

	for (Strategy* player : winners) {
		player->addWin();
		std::string winnerMsg = ConnectionConstants::CMD_BROADCAST_WINNER + player->getName();
		connection->sendMessage(winnerMsg);
	}
}

/*
 * Returns a list of all the winners in a round. If the turns are not
 * finished (the players have not taken their turns), then only players dealt
 * a natural blackjack are considered winners. If the turns are finished, the players
 * with the highest value hand are winners.
 */
std::vector<Strategy*> BlackjackGame::getWinners(bool turnsAreFinished) {
	std::vector<Strategy*> winners;

	if (!turnsAreFinished) {
		for (Strategy* player : players) {
			if (player->hasNaturalBlackjack() && player != dealer) {
				winners.push_back(player);
			}
		}

		return winners;
	}

	for (Strategy* player : players) {
		if (!player->isBust() && player != dealer && (player->getHandValue() >= dealer->getHandValue() || dealer->isBust())) {
			winners.push_back(player);
		}
	}

	return winners;
}

void BlackjackGame::stopGame() {
	gameIsRunning = false;
	players.clear();
}

std::vector<Strategy*> BlackjackGame::getPlayers() {
	return players;
}

bool BlackjackGame::isGameRunning() {
	return gameIsRunning;
}