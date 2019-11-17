#include "GameConnection.h"

void GameConnection::setName(std::string name) { 
	clientName = name;
}

void GameConnection::setType(CONNECTION_TYPE type) {
    connectionType = type;
}

CONNECTION_TYPE GameConnection::getType() { 
	return connectionType; 
}

std::string GameConnection::getName() {
    return clientName;
}

seasocks::WebSocket* GameConnection::getConnection() { 
	return connection;
}