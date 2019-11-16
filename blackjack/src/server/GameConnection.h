#pragma once

#include <string>
#include "../seasocks/src/main/c/seasocks/WebSocket.h"

namespace connection {

const enum CONNECTION_TYPE { WEB_CLIENT = 0, C_CLIENT };

class GameConnection {
   public:
    GameConnection(WebSocket* conn) : connection(conn){};
    
	void setName(std::string name);
    void setType(CONNECTION_TYPE type);

	WebSocket* getConnection();
    std::string getName();
    CONNECTION_TYPE getType();

   private:
    CONNECTION_TYPE connectionType;
    std::string clientName;
    WebSocket* connection;
};

}  // namespace connection