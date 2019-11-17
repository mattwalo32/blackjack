#pragma once

#include "../seasocks/src/main/c/seasocks/WebSocket.h"
#include "GameConnection.h"

#include <string>

class GameConnectionManager {
public:
    ~GameConnectionManager();

	void processCommand(seasocks::WebSocket* connection, std::string cmd);
	void addConnection(seasocks::WebSocket* conn);
    void removeConnection(seasocks::WebSocket* conn);

private:
    std::vector<GameConnection*> connections;
	int numConnections = 0;
	
	GameConnection* getGameConnection(seasocks::WebSocket* connection);
	bool cmdHasPrefix(std::string cmd, std::string prefix);
};