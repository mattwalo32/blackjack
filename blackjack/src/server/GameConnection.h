#pragma once

#include <string>
#include "ConnectionConstants.h"
#include "../seasocks/src/main/c/seasocks/WebSocket.h"

using namespace ConnectionConstants;

class GameConnection {
   public:
    GameConnection(seasocks::WebSocket* conn) : connection(conn){};
    
	void setName(std::string name);
    void setType(CONNECTION_TYPE type);

	seasocks::WebSocket* getConnection();
    std::string getName();
    CONNECTION_TYPE getType();

   private:
    CONNECTION_TYPE connectionType;
    seasocks::WebSocket* connection;
    std::string clientName = "";
};