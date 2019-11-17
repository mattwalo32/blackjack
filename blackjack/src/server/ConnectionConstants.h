#pragma once

#include <string>

namespace ConnectionConstants {

	enum CONNECTION_TYPE { WEB_CLIENT = 0, C_CLIENT };

    const int MAX_NUM_CONNECTION = 6;

	const std::string CMD_NAME = "SETNAME:";
	const std::string CMD_TYPE = "SETTYPE:";
};