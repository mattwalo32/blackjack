#include "Player.h"

using namespace GameConstants;

Player::Player(ConnectionListener* listener, std::string name, int startingBalance) {
	this->name = name;
	balance = startingBalance;
	currentHandScore = 0;
	busted = false;
	naturalBlackjack = false;
    isDealer = false;
	connection = listener;
}

/*
 * Adds the card to the players hand, updates score, and notifies server.
 */
void Player::dealCard(Card card) {
	currentHand.push_back(card);
	updateScore();
	connection->sendMessage(card.getCode() + ":" + name);
}

bool Player::wantsToHit() {
	std::vector<std::string> validResponses = { ConnectionConstants::CMD_STAY, ConnectionConstants::CMD_HIT };
	
	WsMessage response = getPlayerResponse(validResponses, [this](WsMessage msg) {
		cout << "NAME: " << msg.getSenderName() << endl;
		return msg.getSenderName() == this->getName();
	});

	cout << endl << endl << response.getSenderName() << " " << response.getPrefix() << endl;

	return response.getPrefix() == ConnectionConstants::CMD_HIT;
}

/*
 * Waits for a response from the user. This method will wait a certain amount
 * of time and notify the server how much time is left. If the time runs out
 * or the user takes their turn, this method returns.
 */
WsMessage Player::getPlayerResponse(std::vector<std::string> expectedPrefixes, validationFunc isValid) {
	int secondsLeft = GameConstants::TURN_TIME_SECONDS;
	unsigned __int64 startTime = TimeUtils::systemTimeMillis();
	unsigned __int64 currentTime = startTime;


	while (startTime + GameConstants::TURN_TIME_MILLIS > currentTime) {
		currentTime = TimeUtils::systemTimeMillis();

		// Message of format TIMELEFT:19:Username
		connection->sendMessage(ConnectionConstants::CMD_TIMELEFT +
			std::to_string(secondsLeft) + ":" + name);

		std::vector<WsMessage> messages = connection->clearBuffer();
		for (WsMessage message : messages) {
			for (std::string prefix : expectedPrefixes) {
				cout << message.getPrefix() << endl;
				if (ConnectionUtils::cmdHasPrefix(message.getPrefix(), prefix))
					if (isValid(message))
						return message;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 - (TimeUtils::systemTimeMillis() - currentTime)));
		secondsLeft--;
	}

	return WsMessage("");
}