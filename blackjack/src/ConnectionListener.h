#pragma once

#include "GameConstants.h"
#include "ofxLibwebsockets.h"
#include "GameManager.h"


class ConnectionListener {

	public:
		ConnectionListener(GameManager manager);

		// Implemented methods from ofxLibwebsockets library
		void initConnection();
		void onConnect(ofxLibwebsockets::Event& args);
		void onOpen(ofxLibwebsockets::Event& args);
		void onClose(ofxLibwebsockets::Event& args);
		void onIdle(ofxLibwebsockets::Event& args);
		void onMessage(ofxLibwebsockets::Event& args);
		void onBroadcast(ofxLibwebsockets::Event& args);


	private:
		ofxLibwebsockets::Client client;
		GameManager gameManager;
};
