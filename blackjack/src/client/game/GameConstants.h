#pragma once

#include <string>
#include "../../server/ConnectionConstants.h"
#include "Card.h"

namespace GameConstants {
	// Graphics
	const float WINDOW_ASPECT_RATIO = 1.71666;
	const int DEFAULT_WINDOW_WIDTH = 1236; // Background image is 412 x 240
	const int DEFAULT_WINDOW_HEIGHT = 720;
	const float CARD_ASPECT_RATIO = 1.66;
	const float PERCENT_CARD_WIDTH = 0.055;
	const int MIDDLE_TABLE_INDEX = 3;
	const float CARD_STACK_OFFSET[2] = { -0.03, 0.03 };
	const float DEALER_LOCATION[3] = { 0.5, 0.15, 0 };
	const float TABLE_LOCATIONS[7][3] = { {0.183, 0.614, 0.60} , {0.28, 0.713, 0.40}, {0.388, 0.767, 0.20}, {0.5, 0.790, 0},
										  {0.614, 0.767, -0.20}, {0.722, 0.713, -0.40}, {0.820, 0.614, -0.60} };

	// Connection
	const std::string HOST_NAME = "localhost";
	const std::string CHANNEL = "/socket";
	const int PORT = 9090;

	// Client commandsZ
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
}