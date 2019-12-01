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
		int lastDelimIndex = rawMessage.find_last_of(":");
		int firstDelimIndex = rawMessage.find(":");
		messageContents = rawMessage.substr(0, lastDelimIndex);
		prefix = rawMessage.substr(0, firstDelimIndex + 1);

		if (rawMessage.length() - 1 > lastDelimIndex) {
			senderName = rawMessage.substr(lastDelimIndex + 1);
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

std::string WsMessage::getPrefix() {
	return prefix;
}

bool WsMessage::msgHasSender() {
	return hasSender;
}