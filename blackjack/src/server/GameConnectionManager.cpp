#include "GameConnectionManager.h"
#include "ConnectionConstants.h"

using namespace ConnectionConstants;

GameConnectionManager::~GameConnectionManager() { connections.clear(); }

void GameConnectionManager::addConnection(seasocks::WebSocket* conn) {
    GameConnection* connection = new GameConnection(conn);

    if (numConnections >= MAX_NUM_CONNECTION) {
		conn->send(MSG_GAME_FULL);
        return;
    }

    connections.push_back(connection);
    numConnections += 1;
}

void GameConnectionManager::removeConnection(seasocks::WebSocket* socket) {
    int index = 0;
    bool connFound = false;

    for (auto conn : connections) {
        if (conn->getConnection() == socket) {
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

void GameConnectionManager::processCommand(seasocks::WebSocket* connection, std::string cmd) {
    GameConnection* conn = getGameConnection(connection);

    // Set Connection Type
    if (cmdHasPrefix(cmd, CMD_TYPE)) {
        std::string type = cmd.substr(CMD_TYPE.length() - 1);

		if (type == "0") {
			conn->setType(CONNECTION_TYPE::WEB_CLIENT);
		} else if (type == "1") {
			if (cClient != nullptr) {
				connection->send(MSG_C_CLIENT_EXISTS);
				return;
			}

			conn->setType(CONNECTION_TYPE::C_CLIENT);
			cClient = getGameConnection(connection);
		}
    }

	// Only allow commands to be processed if there is a c client.
	if (cClient == nullptr) {
		connection->send(MSG_NO_C_CLIENT);
		return;
	}

    // Set Name
    if (cmdHasPrefix(cmd, CMD_NAME)) {
        std::string name = cmd.substr(CMD_NAME.length() - 1);

        conn->setName(name);
    }
	// Deal Card
	else if (conn->getType() == CONNECTION_TYPE::C_CLIENT && 
			   cmd.length > CARD_COMMAND_SPLIT_INDEX + 1 &&
               cmd[CARD_COMMAND_SPLIT_INDEX] == ':') {
		int cardCode;

        try {
            int cardCode = std::stoi(cmd.substr(0, CARD_COMMAND_SPLIT_INDEX + 1));
        } catch (std::exception e) {
			return;
		}

		if (cardCode >= NUM_CARDS_IN_DECK)
			return;

		const std::string dealMsg = CMD_SEND_CARD + std::to_string(cardCode);
		
		std::string playerName = cmd.substr(CARD_COMMAND_SPLIT_INDEX);
		GameConnection* gameConnection = getConnectionByName(playerName);

		gameConnection->getConnection()->send(dealMsg);
    }
}

/*
 * Given a WebSocket connection object, a pointer to the corresponding
 * GameConnection object is returned.
 */
GameConnection* GameConnectionManager::getGameConnection(seasocks::WebSocket* connection) {
    for (auto conn : connections) {
        if (conn->getConnection() == connection) 
			return conn;
    }

    throw std::runtime_error("No GameConnection found.");
}

/*
 * Given the name of a websocket connection object, a pointer to the corresponding
 * GameConnection object is returned.
 */
GameConnection* GameConnectionManager::getConnectionByName(std::string name) {
    for (auto conn : connections) {
        if (conn->getName() == name) 
			return conn;
    }

    throw std::runtime_error("No GameConnection found.");
}

/*
 * Checks if the given command starts the the given prefix.
 */
bool GameConnectionManager::cmdHasPrefix(std::string cmd, std::string prefix) {
    return cmd.length() > prefix.length() &&
           cmd.substr(0, prefix.length()) == prefix;
}

/*
 *  Closes all connections and resets any state variables.
 */
void GameConnectionManager::reset() {
	for (auto conn : connections) {
		conn->getConnection()->close();
	}

	connections.clear();
	cClient = nullptr;
}