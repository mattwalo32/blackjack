#pragma once

#include <string>

class WsMessage {
public:
	WsMessage(std::string message);
	std::string getMessageContents();
	std::string getSenderName();
	bool msgHasSender();

private:
	std::string rawMessage;
	std::string messageContents;
	std::string senderName;
	bool hasSender;

};