#include "GameManager.h"
#include "Dealer.h"

GameManager::~GameManager() {
	players.clear();
	delete game;
}

void GameManager::init() {
	connListener.setNameUpdateCallback([this](WsMessage msg) {
		this->updatePlayerName(msg);
	});

	connListener.setAddUserCallback([this](WsMessage msg) {
		this->addPlayer(msg);
	});

	connListener.initConnection();
}

void GameManager::updatePlayerName(WsMessage msg) {
	if (msg.getMessageContents().find(":") == string::npos)
		return;

	int delimIndex = msg.getMessageContents().find(":");
	std::string newName = msg.getMessageContents().substr(delimIndex + 1);

	Strategy* playerToUpdate = nullptr;

	for (Strategy* player : this->getPlayers()) {
		if (player->getName() == msg.getSenderName()) {
			playerToUpdate = player;
			break;
		}
	}

	if (playerToUpdate) {
		playerToUpdate->setName(newName);
		cout << "updated " << msg.getSenderName() << " to " << newName;
	}
}

void GameManager::addPlayer(WsMessage msg) {
	Player* player = new Player(&connListener, msg.getSenderName(), GameConstants::STARTING_CASH);
	players.push_back(player);
	cout << "Added " << player->getName() << endl;
}

void GameManager::startGame() {
	cout << "Starting Game" << endl;
	players.push_back(new Dealer());
	game = new BlackjackGame(players, &connListener);
	game->startGame();
}

std::vector<Strategy*> GameManager::getPlayers() {
	return players;
}