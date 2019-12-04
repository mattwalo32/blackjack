#include "BlackjackGame.h"

using namespace TimeUtils;

BlackjackGame::BlackjackGame(std::vector<Strategy*> players, ConnectionListener* listener) {
	this->players = players;
	connection = listener;
	gameIsRunning = false;

	int tableLocationOffset = 3 - (players.size() / 2);

	for (int i = 0; i < players.size(); i++) {
		Strategy* strategy = players.at(i);

		int tableLocIndex = i + tableLocationOffset;

		strategy->tableLocationX = GameConstants::TABLE_LOCATIONS[tableLocIndex][0];
		strategy->tableLocationY = GameConstants::TABLE_LOCATIONS[tableLocIndex][1];
		strategy->angle = GameConstants::TABLE_LOCATIONS[tableLocIndex][2];

		if (strategy->playerIsDealer())
			dealer = strategy;
	}
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
		winners.clear();
		clearHand();
		std::this_thread::sleep_for(std::chrono::seconds(GameConstants::ROUND_RESET_DELAY_SEC));
	}
}
//TODO: Make sure deck isn't empty

void BlackjackGame::dealCards() {
	for (int cardNum = 0; cardNum < GameConstants::NUM_STARTING_CARDS; cardNum++) {
		for (Strategy* player : players) {
			Card card = deck.drawCard();
			player->dealCard(card);
			cout << "Dealt " << card.getRank() << " of " << card.getSuit() << " to " << player->getName() << endl;
		}
	}
}

/*
 * See if each player wants to hit or stay. May freeze thread while waiting
 * for response.
 */
void BlackjackGame::takeTurns() {
	for (Strategy* player : players) {
		cout << "Taking " << player->getName() << "'s turn" << endl;
		while (!player->isBust() && player->wantsToHit()) {
			cout << player->getName() << " drew a card" << endl;
			player->dealCard(deck.drawCard());
			cout << "Taking " << player->getName() << "'s turn" << endl;
		}
		cout << player->getName() << "'s turn is over" << endl;
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
		if (!player->isBust() && player->getHandValue() >= dealer->getHandValue() && player != dealer) {
			winners.push_back(player);
		}
	}

	return winners;
}

std::vector<Strategy*> BlackjackGame::getPlayers() {
	return players;
}