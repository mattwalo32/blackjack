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

/*
 * calculates the score of their
 * hand, if they busted, and if they have a natural blackjack(10 card and ace).
 * Since aces can be either 1s or 11s, the best valid score of the player is
 * taken.For example with the hand "3, 4, ACE, ACE" The value would be 19 because
 * the first ACE would be assigned 11 and the second 1, totaling 3 + 4 + 11 + 1 = 19.
 */
void Player::updateScore() {
	int numAces = 0;
	int scoreBeforeAces = 0;
	int bestScore = 0;

	// Add up everything besides the aces
	for (Card card : currentHand) {
		if (card.getRank() == Card::ACE) {
			numAces++;
			continue;
		}

		scoreBeforeAces += card.getValue();
	}

	if (numAces == 0)
		bestScore = scoreBeforeAces;

	// Calculate best possible hand with aces
	for (int numHighStates = 0; numHighStates <= numAces; numHighStates++) {
		int sumOfAces = numHighStates * ACE_HIGH_VALUE + (numAces - numHighStates) * ACE_LOW_VALUE;
		int totalScore = scoreBeforeAces + sumOfAces;

		if (totalScore > bestScore && (totalScore <= WINNING_VALUE || bestScore == 0)) {
			bestScore = totalScore;
		}
	}

	busted = bestScore > WINNING_VALUE;
	naturalBlackjack = currentHand.size() == 2 && bestScore == WINNING_VALUE;
	currentHandScore = bestScore;
}

bool Player::wantsToHit() {
	std::vector<std::string> validResponses = { ConnectionConstants::CMD_STAY, ConnectionConstants::CMD_HIT };
	
	WsMessage response = getPlayerResponse(validResponses, [this](WsMessage msg) {
		return msg.getSenderName() == this->getName();
	});

	return response.getMessageContents() + ":" == ConnectionConstants::CMD_HIT;
}

/*
 * Waits for a response from the user. This method will wait a certain amount
 * of time and notify the server how much time is left. If the time runs out
 * or the user takes their turn, this method returns.
 */
WsMessage Player::getPlayerResponse(std::vector<std::string> expectedPrefixes, validationFunc isValid) {
	int secondsLeft = GameConstants::TURN_TIME_MILLIS;
	unsigned __int64 startTime = TimeUtils::systemTimeMillis();
	unsigned __int64 currentTime = startTime;


	while (startTime + GameConstants::TURN_TIME_MILLIS > currentTime) {
		currentTime = TimeUtils::systemTimeMillis();

		// Message of format TIMELEFT:19:Username
		connection->sendMessage(ConnectionConstants::CMD_TIMELEFT +
			std::to_string(secondsLeft) + ":" + name);

		std::vector<WsMessage> messages = connection->clearBuffer();
		for (WsMessage message : messages) {
			for (std::string command : expectedPrefixes) {
				std::string prefix = command.substr(0, command.length - 1);
				if (ConnectionUtils::cmdHasPrefix(message.getMessageContents(), prefix))
					if (isValid(message))
						return message;
			}
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(1000 - (TimeUtils::systemTimeMillis() - currentTime)));
		secondsLeft--;
	}

	return WsMessage("");
}


void Player::addToBalance(int amount) {
	balance += amount;
}

void Player::removeFromBalance(int amount) {
	balance -= amount;
}

void Player::clearHand() {
	currentHand.clear();
	currentBet = 0;
	busted = false;
}

void Player::setCurrentBet(int betAmount) {
	currentBet = betAmount;
}

int Player::getBalance() {
	return balance;
}

int Player::getCurrentBet() {
	return currentBet;
}

bool Player::isBust() {
	return busted;
}

bool Player::hasNaturalBlackjack() {
	return naturalBlackjack;
}

bool Player::playerIsDealer() {
	return isDealer;
}

std::string Player::getName() {
	return name;
}