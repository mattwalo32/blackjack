#include "GameConnectionManager.h"
#include "ConnectionConstants.h"

using namespace ConnectionConstants;

void GameConnectionManager::addConnection(WebSocket* conn) {
    connection::GameConnection connection(conn);

	if (numConnections >= MAX_NUM_CONNECTION) {
        std::cout << "Max capacity reached";
        return;
	}
    
	connections.push_back(connection);
	numConnections += 1;
}

void GameConnectionManager::removeConnection(WebSocket* conn) {
    int index = 0;
    bool connFound = false;

	for (auto conn : connections) {
        if (conn.getConnection == conn) {
            connFound = true;
            break;
        }

		index += 1;
    } 

	if (connFound) {
        connections.erase(connections.begin() + index);
        numConnections -= 1;
    }
}

void GameConnectionManager::processCommand(WebSocket* connection, std::string cmd) {
	if (cmdHasPrefix(cmd, CMD_NAME)) {
        std::string name = cmd.substr(CMD_NAME.length - 1);

        connection::GameConnection* conn = getGameConnection(connection);
        conn->setName(name);
        std::cout << conn->getName();
	}
}

/*
 * Given a WebSocket connection object, a pointer to the corresponding GameConnection 
 * object is returned.
 */
connection::GameConnection* GameConnectionManager::getGameConnection(WebSocket* connection) {
    for (auto conn : connections) {
        if (conn.getConnection == connection) 
			return &conn;
	} 

	throw std::runtime_error("No GameConnection found.");
}

/*
 * Checks if the given command starts the the given prefix.
 */
bool GameConnectionManager::cmdHasPrefix(std::string cmd, std::string prefix) {
    return cmd.length > prefix.length && cmd.substr(0, prefix.length) == prefix;
}