#pragma once

#include "../seasocks/src/main/c/seasocks/WebSocket.h"
#include "GameConnection.h"

#include <string>

class GameConnectionManager {
public:
	void processCommand(WebSocket* connection, std::string cmd);
	void addConnection(WebSocket* conn);
    void removeConnection(WebSocket* conn);

private:
    std::vector<connection::GameConnection> connections;
	int numConnections = 0;
	
	connection::GameConnection* getGameConnection(WebSocket* connection);
	bool cmdHasPrefix(std::string cmd, std::string prefix);
};