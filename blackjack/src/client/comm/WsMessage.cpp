#include "WsMessage.h"

/*
 * Stores information about the message such as who sent it, the
 * raw message, and the condensed message (without sender name). It is
 * expected that all messages to the client will end with a colon followed
 * by the sender name. This part can be removed from the end and stored
 * as the sender name. This is not extremely secure as messages can
 * be easily immitated, but that doesn't really matter for blackjack.
 */
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
	} else {
		messageContents = rawMessage;
		senderName = "";
		hasSender = false;
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