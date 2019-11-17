#pragma once

#include "../seasocks/src/main/c/seasocks/WebSocket.h"
#include "GameConnection.h"

#include <string>

class GameConnectionManager {
public:
    ~GameConnectionManager();

	void addConnection(seasocks::WebSocket* conn);
    void removeConnection(seasocks::WebSocket* conn);

	void processCommand(seasocks::WebSocket* connection, std::string cmd);
	void setConnectionType(seasocks::WebSocket* connection, std::string type);
	void sendCard(seasocks::WebSocket* connection, std::string playerCode, std::string cardCode);
	
	void reset();

private:
    std::vector<GameConnection*> connections;
	GameConnection* cClient;
	int numConnections = 0;
	
	GameConnection* getGameConnection(seasocks::WebSocket* connection);
    GameConnection* getConnectionByName(std::string name);
	bool cmdHasPrefix(std::string cmd, std::string prefix);
};