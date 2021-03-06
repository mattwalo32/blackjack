#pragma once

#include <string>
#include <vector>
#include "game/GameConstants.h"
#include "comm/WsMessage.h"
#include "ofxLibwebsockets.h"
#include "../server/utils/ConnectionUtils.h"


typedef std::function<void(WsMessage)> msgCallback;

class ConnectionListener {

	public:
		std::vector<WsMessage> clearBuffer();
		void sendMessage(std::string message);
		void setNameUpdateCallback(msgCallback callback);
		void setAddUserCallback(msgCallback callback);

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
		msgCallback nameUpdateCallback;
		msgCallback addUserCallback;
		ofxLibwebsockets::Client client;

};
