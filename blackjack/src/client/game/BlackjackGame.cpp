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
	}
}

/*
 * Waits for a response from the user. This method will wait a certain amount
 * of time and notify the server how much time is left. If the time runs out
 * or the user takes their turn, this method returns.
 */
void BlackjackGame::waitForResponse() {
	int secondsLeft = GameConstants::TURN_TIME_MILLIS;
	unsigned __int64 currentTime = 0;
	unsigned __int64 startTime = systemTimeMillis();


	while (startTime + GameConstants::TURN_TIME_MILLIS > currentTime) {
		currentTime = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now().time_since_epoch()).count();
		
		std::vector<std::string> messages = connection->clearBuffer();
	


		std::this_thread::sleep_for(std::chrono::seconds(1 - ));
		secondsLeft--;
	} 

}
