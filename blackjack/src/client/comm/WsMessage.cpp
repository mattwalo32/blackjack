#include "WsMessage.h"

WsMessage::WsMessage(std::string message) {
	rawMessage = message;

	if (rawMessage.find(":") != std::string::npos) {
		int delimIndex = rawMessage.find_last_of(":");
		messageContents = rawMessage.substr(0, delimIndex);

		if (rawMessage.length - 1 > delimIndex) {
			senderName = rawMessage.substr(delimIndex + 1);
			hasSender = true;
		} else {
			senderName = "";
			hasSender = false;
		}
	}
}

std::string WsMessage::getMessageContents() {
	return messageContents;
}

std::string WsMessage::getSenderName() {
	return senderName;
}

bool WsMessage::msgHasSender() {
	return hasSender;
}