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
	void setConnectionType(GameConnection* connection, std::string type);
	void setConnectionName(GameConnection* connection, std::string newName);
	void sendCard(GameConnection* connection, std::string playerName, std::string cardCode);
	void notifyUserTime(std::string cmd);
	void notifyUserTurnOver(std::string cmd);
	
	void reset();

private:
    std::vector<GameConnection*> connections;
	GameConnection* cClient;
	int numConnections = 0;
	
	GameConnection* getGameConnection(seasocks::WebSocket* connection);
    GameConnection* getConnectionByName(std::string name);
};