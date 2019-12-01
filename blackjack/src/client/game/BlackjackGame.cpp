#include "BlackjackGame.h"

using namespace TimeUtils;

BlackjackGame::BlackjackGame(std::vector<Player*> players, ConnectionListener* listener) {
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
		//placeBets();
		cout << "Dealing cards" << endl;
		dealCards();
		cout << "Taking player turns" << endl;
		//TODO: Check for blackjacks
		takeTurns();
	}
}

/*void BlackjackGame::placeBets() {
	for (Player* player : players) {
		currentPlayer = player;

		WsMessage response = getPlayerResponse({ ConnectionConstants::CMD_BET },
			[](WsMessage message, Player* currentPlayer) {
			
			if (message.getSenderName() != currentPlayer->getName())
				return false;

			std::string amountStr = message.getMessageContents();
			int bet;

			try {
				bet = std::stoi(amountStr);
			} catch (std::exception e) {
				return false;
			}

			return bet <= currentPlayer->getBalance();
		});

		int bet = std::stoi(response.getMessageContents());

		//TODO: Finish implementing
	}
}*/

//TODO: Make sure deck isn't empty

void BlackjackGame::dealCards() {
	for (int cardNum = 0; cardNum < GameConstants::NUM_STARTING_CARDS; cardNum++) {
		for (Player* player : players) {
			Card card = deck.drawCard();
			player->dealCard(card);
			cout << "Dealt " << card.getRank() << " of " << card.getSuit() << " to " << player->getName();
		}
	}
}

/*
 * See if each player wants to hit or stay. May freeze thread while waiting
 * for response.
 */
void BlackjackGame::takeTurns() {
	for (Player* player : players) {
		cout << "Taking " << player->getName() << "'s turn" << endl;
		while (!player->isBust() && player->wantsToHit()) {
			cout << player->getName() << " drew a card" << endl;
			player->dealCard(deck.drawCard());
			cout << "Taking " << player->getName() << "'s turn" << endl;
		}
		cout << player->getName() << "'s turn is over" << endl;
	}
}

/*
 * Waits for a response from the user. This method will wait a certain amount
 * of time and notify the server how much time is left. If the time runs out
 * or the user takes their turn, this method returns.
 */
/*WsMessage BlackjackGame::getPlayerResponse(std::vector<std::string> expectedPrefixes, validationFunction isValid) {
	int secondsLeft = GameConstants::TURN_TIME_MILLIS;
	unsigned __int64 startTime = systemTimeMillis();
	unsigned __int64 currentTime = startTime;


	while (startTime + GameConstants::TURN_TIME_MILLIS > currentTime) {
		currentTime = systemTimeMillis();
		
		connection->sendMessage(ConnectionConstants::CMD_TIMELEFT + 
			currentPlayer->getName() + ":" + std::to_string(secondsLeft));

		std::vector<WsMessage> messages = connection->clearBuffer();
		for (WsMessage message : messages) {
			for (std::string prefix : expectedPrefixes) {
				if (ConnectionUtils::cmdHasPrefix(message.getMessageContents(), prefix))
					if(isValid(message, currentPlayer))
					// TODO: Check response is valid
						return message;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 - (systemTimeMillis() - currentTime)));
		secondsLeft--;
	} 

	return "";
}*/
