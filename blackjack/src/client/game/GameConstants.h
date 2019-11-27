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
}