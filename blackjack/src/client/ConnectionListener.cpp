#include "ConnectionListener.h"

using namespace ConnectionUtils;

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

void ConnectionListener::setNameUpdateCallback(msgCallback callback) {
	nameUpdateCallback = callback;
}

void ConnectionListener::setAddUserCallback(msgCallback callback) {
	addUserCallback = callback;
}

void ConnectionListener::setRmUserCallback(msgCallback callback) {
	rmUserCallback = callback;
}

void ConnectionListener::sendMessage(std::string message) {
	client.send(message);
}

std::vector<WsMessage> ConnectionListener::clearBuffer() {
	std::vector<WsMessage> messages = messageBuffer;
	messageBuffer.clear();
	return messages;
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

}

void ConnectionListener::onMessage(ofxLibwebsockets::Event& args) {
	WsMessage msg(args.message);
	messageBuffer.push_back(msg);

	// cout << msg.getMessageContents() << " From " << msg.getSenderName() << endl;

	if (cmdHasPrefix(msg.getPrefix(), ConnectionConstants::CMD_UPDATE_NAME)) {
		nameUpdateCallback(msg);
	} else if (cmdHasPrefix(msg.getPrefix(), ConnectionConstants::CMD_ADD_USER)) {
		addUserCallback(msg);
	}// else if (cmdHasPrefix(msg.getPrefix(), ConnectionConstants::CMD_RM_USER)) {
	//	rmUserCallback(msg);
	//}

}

void ConnectionListener::onBroadcast(ofxLibwebsockets::Event& args) {
	WsMessage msg(args.message);
	messageBuffer.push_back(msg);
}