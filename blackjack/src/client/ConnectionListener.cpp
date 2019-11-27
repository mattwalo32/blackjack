#include "ConnectionListener.h"

ConnectionListener::ConnectionListener(GameManager manager) {
	gameManager = manager;
}

// Open connection and set type to C client
void ConnectionListener::initConnection(){
	ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();

	options.host = GameConstants::HOST_NAME;
	options.port = GameConstants::PORT;
	options.channel = GameConstants::CHANNEL;

	client.connect(options);
	client.addListener(this);

	client.send(GameConstants::CMD_SET_C_CLIENT);
}

void ConnectionListener::onConnect(ofxLibwebsockets::Event& args) {
	cout << "on connected" << endl;
}

void ConnectionListener::onOpen(ofxLibwebsockets::Event& args) {
	cout << "on open" << endl;
}

void ConnectionListener::onClose(ofxLibwebsockets::Event& args) {
	cout << "on close" << endl;
}

void ConnectionListener::onIdle(ofxLibwebsockets::Event& args) {
	cout << "on idle" << endl;
}

void ConnectionListener::onMessage(ofxLibwebsockets::Event& args) {
	cout << "got message " << args.message << endl;
}

void ConnectionListener::onBroadcast(ofxLibwebsockets::Event& args) {
	cout << "got broadcast " << args.message << endl;
}