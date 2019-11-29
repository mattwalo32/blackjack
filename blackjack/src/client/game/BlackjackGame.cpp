#include "BlackjackGame.h"

using namespace TimeUtils;

BlackjackGame::BlackjackGame(std::vector<Player> players, ConnectionListener* listener) {
	this->players = players;
	connection = listener;
	gameIsRunning = false;
}

/*
 * Runs through a game of blackjack until there are no players left. This
 * method should be run on another thread or the UI will be blocked.
 */
void BlackjackGame::startGame() {
	gameIsRunning = true;
	//TODO: Set current player
	while (gameIsRunning) {
		placeBets();
		dealCards();
		//TODO: Check for blackjacks
		takeTurns();
	}
}

void BlackjackGame::placeBets() {
	for (Player player : players) {

	}
}

void BlackjackGame::dealCards() {

}

void BlackjackGame::takeTurns() {

}

/*
 * Waits for a response from the user. This method will wait a certain amount
 * of time and notify the server how much time is left. If the time runs out
 * or the user takes their turn, this method returns.
 */
std::string BlackjackGame::waitForResponse(std::vector<std::string> expectedPrefixes) {
	int secondsLeft = GameConstants::TURN_TIME_MILLIS;
	unsigned __int64 startTime = systemTimeMillis();
	unsigned __int64 currentTime = startTime;


	while (startTime + GameConstants::TURN_TIME_MILLIS > currentTime) {
		currentTime = systemTimeMillis();
		
		connection->sendMessage(ConnectionConstants::CMD_TIMELEFT + 
			currentPlayer->getName() + ":" + std::to_string(secondsLeft));

		std::vector<std::string> messages = connection->clearBuffer();
		for (std::string message : messages) {
			for (std::string prefix : expectedPrefixes) {
				if (ConnectionUtils::cmdHasPrefix(message, prefix))
					return message;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 - (systemTimeMillis() - currentTime)));
		secondsLeft--;
	} 

	return "";
}
