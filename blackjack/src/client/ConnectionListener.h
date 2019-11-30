#pragma once

#include <string>
#include <vector>
#include "game/GameConstants.h"
#include "game/GameManager.h"
#include "comm/WsMessage.h"
#include "ofxLibwebsockets.h"


class ConnectionListener {

	public:
		ConnectionListener();
		void sendMessage(std::string message);
		std::vector<WsMessage> clearBuffer();

		// Implemented methods from ofxLibwebsockets library
		void initConnection();
		void onConnect(ofxLibwebsockets::Event& args);
		void onOpen(ofxLibwebsockets::Event& args);
		void onClose(ofxLibwebsockets::Event& args);
		void onIdle(ofxLibwebsockets::Event& args);
		void onMessage(ofxLibwebsockets::Event& args);
		void onBroadcast(ofxLibwebsockets::Event& args);


	private:
		std::vector<WsMessage> messageBuffer;
		ofxLibwebsockets::Client client;

};
