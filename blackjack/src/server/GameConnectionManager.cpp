#include "GameConnectionManager.h"
#include "ConnectionConstants.h"

using namespace ConnectionConstants;

GameConnectionManager::~GameConnectionManager() { connections.clear(); }

/*
 * Should be called whenever a connection is added to the websocket server.
 * Checks that server is not full, and adds connection to connection list.
 */
void GameConnectionManager::addConnection(seasocks::WebSocket* conn) {
    GameConnection* connection = new GameConnection(conn);

    if (numConnections >= MAX_NUM_CONNECTION) {
		conn->send(MSG_GAME_FULL);
        return;
    }

    connections.push_back(connection);
    numConnections += 1;
}

/*
 * Should be called whenever a connection disconnects from the server.
 * Searches for the connection and removes it from the connection list.
 * If the connection is the C Client, the game will end.
 */
void GameConnectionManager::removeConnection(seasocks::WebSocket* socket) {
    int index = 0;
    bool connFound = false;
	bool connIsCClient = false;

    for (auto conn : connections) {
        if (conn->getConnection() == socket) {
            connFound = true;
			connIsCClient = conn == cClient;
            break;
        }

        index += 1;
    }

    if (connFound) {
        connections.erase(connections.begin() + index);

		//TODO: Notify players
		if (connIsCClient)
			reset();

        numConnections -= 1;
    }
}

/*
 * This is the main method for handling communication between clients. All
 * incomin commands are handled. If there is not c client, the only command that
 * will be handled is the 'set type' command.
 */
void GameConnectionManager::processCommand(seasocks::WebSocket* connection, std::string cmd) {
    GameConnection* conn = getGameConnection(connection);

    // Set Connection Type
    if (cmdHasPrefix(cmd, CMD_TYPE)) {
		std::string type = cmd.substr(CMD_TYPE.length() - 1);
		setConnectionType(connection, type);
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
		std::string playerCode = cmd.substr(0, CARD_COMMAND_SPLIT_INDEX + 1);
		std::string cardCode = cmd.substr(CARD_COMMAND_SPLIT_INDEX);

		sendCard(conn, playerCode, cardCode);
    }
}

void GameConnectionManager::setConnectionType(GameConnection* connection, std::string type) {
	if (type == "0") {
		connection->setType(CONNECTION_TYPE::WEB_CLIENT);
	} else if (type == "1") {
		
		if (cClient != nullptr) {
			connection->getConnection()->send(MSG_C_CLIENT_EXISTS);
			return;
		}

		connection->setType(CONNECTION_TYPE::C_CLIENT);
		cClient = connection;
	}
}

void GameConnectionManager::sendCard(GameConnection* connection, std::string playerCode, std::string cardCode) {
	int cardNum;
	int playerNum;
	
	try {
		cardNum = std::stoi(cardCode);
		playerNum = std::stoi(playerCode);
	} catch (std::exception e) {
		return;
	}

	if (cardNum >= NUM_CARDS_IN_DECK || playerNum >= connections.size())
		return;

	const std::string dealMsg = CMD_SEND_CARD + std::to_string(cardNum);
	GameConnection* gameConnection = connections.at(playerNum);
	gameConnection->getConnection()->send(dealMsg);
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