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
	const int DEFAULT_NUM_DECKS = 6;
	const int TURN_TIME_MILLIS = 10 * 1000;

	const int STARTING_CASH = 500;
	const int MIN_BET = 20;
	const int MAX_BET = 200;
}