#include "GameConnection.h"

using connection::GameConnection;

void connection::GameConnection::setName(std::string name) { 
	clientName = name;
}

void connection::GameConnection::setType(connection::CONNECTION_TYPE type) {
    connectionType = type;
}

connection::CONNECTION_TYPE connection::GameConnection::getType() { 
	return connectionType; 
}

std::string connection::GameConnection::getName() {
    return clientName;
}

WebSocket* connection::GameConnection::getConnection() { 
	return connection;
}