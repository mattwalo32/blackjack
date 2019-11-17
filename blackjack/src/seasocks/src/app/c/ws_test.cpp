// Copyright (c) 2013-2017, Matt Godbolt
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// Redistributions of source code must retain the above copyright notice, this
// list of conditions and the following disclaimer.
//
// Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

// An extraordinarily simple test which presents a web page with some buttons.
// Clicking on the numbered button increments the number, which is visible to
// other connected clients.  WebSockets are used to do this: by the rather
// suspicious means of sending raw JavaScript commands to be executed on other
// clients.

// These import statements are correct, however the IDE may throw errors
#include "seasocks/PrintfLogger.h"
#include "seasocks/Server.h"
#include "seasocks/StringUtil.h"
#include "seasocks/WebSocket.h"
#include "seasocks/util/Json.h"
#include "../../../../server/GameConnectionManager.h"

#include <string>
#include <iostream>
#include <memory>
#include <set>
#include <sstream>
#include <string>

using namespace seasocks;

class MyHandler : public WebSocket::Handler {
public:
    explicit MyHandler(Server* server)
            : _server(server) {
		 
    }

    virtual void onConnect(WebSocket* connection) override {
        connManager.addConnection(connection);
        /*std::cout << "Connected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress())
                  << "\nCredentials: " << *(connection->credentials()) << "\n";*/
    }

    virtual void onData(WebSocket* connection, const char* data) override {
        std::string cmd = data;
        connManager.processCommand(connection, cmd);
    }

    virtual void onDisconnect(WebSocket* connection) override {
        connManager.removeConnection(connection);
        /*std::cout << "Disconnected: " << connection->getRequestUri()
                  << " : " << formatAddress(connection->getRemoteAddress()) << "\n";*/
    }

private:
	const int MAX_CONNECTIONS = 4;
    GameConnectionManager connManager;

    Server* _server;
};

int main(int /*argc*/, const char* /*argv*/[]) {
    auto logger = std::make_shared<PrintfLogger>(Logger::Level::Debug);

    Server server(logger);

    auto handler = std::make_shared<MyHandler>(&server);
    server.addWebSocketHandler("/ws", handler);
    server.serve("src/ws_test_web", 9090);
    return 0;
}
