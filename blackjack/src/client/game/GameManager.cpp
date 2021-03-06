#include "GameManager.h"
#include "Dealer.h"

std::atomic<bool> running(false);

GameManager::~GameManager() {
	players.clear();
	delete game;
}

void GameManager::init() {
	//gameRunning = false;
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
	Player* player = new Player(&connListener, msg.getSenderName());
	players.push_back(player);
	cout << "Added " << player->getName() << endl;
}

void GameManager::startGame() {
	if (players.size() == 0)
		return;

	players.push_back(new Dealer());
	running = true;
	game = new BlackjackGame(&running, players, &connListener);
	game->startGame();
}

std::vector<Strategy*> GameManager::getPlayers() {
	return players;
}

BlackjackGame* GameManager::getRunningGame() {
	return game;
}

void GameManager::stopGame() {
	running = false;
	players.clear();
	//delete game;
}

bool GameManager::isGameRunning() {
	return running.load();
}