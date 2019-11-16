#pragma once

#include <string>
#include "../seasocks/src/main/c/seasocks/WebSocket.h"

namespace connection {

	const enum CONNECTION_TYPE {WEB_CLIENT=0, C_CLIENT};

	class GameConnection {
	public:

	private:
		 CONNECTION_TYPE connectionType;
         std::string clientName;
         WebSocket* connection;


	};

}