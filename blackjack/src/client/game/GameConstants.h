#pragma once

#include <string>
#include "../../server/ConnectionConstants.h"

namespace GameConstants {
	// Graphics
	const int DEFAULT_WINDOW_WIDTH = 1024;
	const int DEFAULT_WINDOW_HEIGHT = 768;

	// Connection
	const std::string HOST_NAME = "localhost";
	const std::string CHANNEL = "/socket";
	const int PORT = 9090;

	// Client commands
	const std::string CMD_SET_C_CLIENT = ConnectionConstants::CMD_TYPE + "1";

	// Game
	const int ACE_LOW_VALUE = 1;
	const int ACE_HIGH_VALUE = 11;
	const int NUM_ACE_VALUES = 2;
	const int WINNING_VALUE = 21;
	const int DEALER_HIT_AMOUNT = 17;

	const int NUM_STARTING_CARDS = 2;
	const int DEFAULT_NUM_DECKS = 6;
	const int ROUND_RESET_DELAY_SEC = 3;
	const int TURN_TIME_SECONDS = 20;
	const int TURN_TIME_MILLIS = TURN_TIME_SECONDS * 1000;

	const int STARTING_CASH = 500;
	const int MIN_BET = 20;
	const int MAX_BET = 200;
}