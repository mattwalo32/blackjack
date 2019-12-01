#include "GameConnectionManager.h"
#include "ConnectionConstants.h"
#include "utils/ConnectionUtils.h"

//TODO: General messages
//TODO: Betting
//TODO: Timeleft

using namespace ConnectionConstants;

GameConnectionManager::~GameConnectionManager() { 
	connections.clear();
}

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
    if (ConnectionUtils::cmdHasPrefix(cmd, CMD_TYPE)) {
		std::string type = cmd.substr(CMD_TYPE.length());
		setConnectionType(conn, type);
		return;
    }

	// Only allow commands to be processed if there is a c client.
	if (cClient == nullptr) {
		connection->send(MSG_NO_C_CLIENT);
		return;
	}

	// Web Client Commands
	if (conn->getType() == CONNECTION_TYPE::WEB_CLIENT) {
		// Set Name
		if (ConnectionUtils::cmdHasPrefix(cmd, CMD_NAME)) {
			std::string name = cmd.substr(CMD_NAME.length());
			setConnectionName(conn, name);
		}

		// Hit or Stay
		if (ConnectionUtils::cmdHasPrefix(cmd, CMD_HIT)) {
			std::string hitCommand = CMD_HIT + conn->getName();
			cClient->getConnection()->send(hitCommand);
		}

		if (ConnectionUtils::cmdHasPrefix(cmd, CMD_STAY)) {
			std::string stayCommand = CMD_STAY + conn->getName();
			cClient->getConnection()->send(stayCommand);
		}
	}

	// C Client Commands
	if (conn->getType() == CONNECTION_TYPE::C_CLIENT) {
		// Send Card to Player
		if (cmd.length() > CARD_COMMAND_SPLIT_INDEX + 1 && cmd[CARD_COMMAND_SPLIT_INDEX] == ':') {
			std::string cardCode = cmd.substr(0, CARD_CODE_LENGTH);
			std::string playerName = cmd.substr(CARD_COMMAND_SPLIT_INDEX + 1);

			sendCard(conn, playerName, cardCode);
		}
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

/*
 * Sets the connection name and notifies the c client. If the name is already
 * taken, the name is not updated and the client notified.
 */
void GameConnectionManager::setConnectionName(GameConnection* connection, std::string name) {
	bool isUpdatingName = !connection->getName().empty();
	std::string cClientMsg;

	if (isUpdatingName)
		cClientMsg = CMD_UPDATE_NAME + name + ":" + connection->getName();
	else
		cClientMsg = CMD_ADD_USER + name;

	if (getConnectionByName(name) != nullptr) {
		connection->getConnection()->send(MSG_NAME_TAKEN);
		return;
	}

	connection->setName(name);
	cClient->getConnection()->send(cClientMsg);
}

void GameConnectionManager::sendCard(GameConnection* connection, std::string playerName, std::string cardCode) {
	int cardNum;
	
	try {
		cardNum = std::stoi(cardCode);
	} catch (std::exception e) {
		return;
	}

	if (cardNum >= NUM_CARDS_IN_DECK)
		return;

	const std::string dealMsg = CMD_SEND_CARD + std::to_string(cardNum);
	GameConnection* gameConnection = getConnectionByName(playerName);
	if(gameConnection != nullptr)
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

	return nullptr;
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