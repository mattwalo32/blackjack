#include "GameConnectionManager.h"
#include "ConnectionConstants.h"
#include "utils/ConnectionUtils.h"
#include <algorithm>

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
	if (!connectionInGame(connection))
		return;

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

		// Notify player of time left
		if (ConnectionUtils::cmdHasPrefix(cmd, CMD_TIMELEFT)) {
			notifyUserTime(cmd);
		}

		// Notify player turn over
		if (ConnectionUtils::cmdHasPrefix(cmd, CMD_TURNEND)) {
			notifyUserTurnOver(cmd);
		}

		// Notify players of round winners
		if (ConnectionUtils::cmdHasPrefix(cmd, CMD_BROADCAST_WINNER)) {
			broadcastWinner(cmd);
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
 * Given the time remaining command, it will extract the recipient name and time
 * remaining from the message and notify the player how much time remains. The command
 * is expected to be the following format: TIMELEFT:<TimeSeconds>:<PlayerName>
 */
void GameConnectionManager::notifyUserTime(std::string cmd) {
	int firstDelimIndex = cmd.find(":");
	int lastDelimIndex = cmd.find_last_of(":");

	std::string timeRemaining = cmd.substr(firstDelimIndex + 1, lastDelimIndex - firstDelimIndex - 1);
	std::string playerName = cmd.substr(lastDelimIndex + 1);
	std::string timeLeftCmd = CMD_TIMELEFT + timeRemaining;

	GameConnection* connection = getConnectionByName(playerName);
	
	if (connection)
		connection->getConnection()->send(timeLeftCmd);
}

/*
 * Given the turn over command, it will extract the recipient name from
 * the message and notify the player that their turn is over. The command
 * is expected to be the following format: ENDTURN:<PlayerName>
 */
void GameConnectionManager::notifyUserTurnOver(std::string cmd) {
	int delimIndex = cmd.find(":");

	std::string playerName = cmd.substr(delimIndex + 1);
	GameConnection* connection = getConnectionByName(playerName);

	if (connection)
		connection->getConnection()->send(CMD_TURNEND);
}

void GameConnectionManager::broadcastWinner(std::string cmd) {
	int delimIndex = cmd.find(":");

	std::string playerName = cmd.substr(delimIndex + 1);

	for (GameConnection* conn : connections) {
		conn->getConnection()->send(cmd);
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

bool GameConnectionManager::connectionInGame(seasocks::WebSocket* connection) {
	for (auto conn : connections) {
		if (conn->getConnection() == connection)
			return true;
	}

	return false;
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