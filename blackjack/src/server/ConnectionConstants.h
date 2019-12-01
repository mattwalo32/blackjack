#pragma once

#include <string>

namespace ConnectionConstants {

	enum CONNECTION_TYPE { WEB_CLIENT = 0, C_CLIENT };

    const int CARD_COMMAND_SPLIT_INDEX = 2;
    const int CARD_CODE_LENGTH = 2;
    const int MAX_NUM_CONNECTION = 6;
    const int NUM_CARDS_IN_DECK = 52;

	const std::string C_CLIENT_WIN_NAME = "Blackjack";

	const std::string CMD_NAME = "SETNAME:";
	const std::string CMD_TYPE = "SETTYPE:";
	const std::string CMD_HIT = "HIT:";
	const std::string CMD_STAY = "STAY:";
	const std::string CMD_SEND_CARD = "SEND:";
	const std::string CMD_ADD_USER = "ADDUSER:";
	const std::string CMD_UPDATE_NAME = "UPDATENAME:";
	const std::string CMD_BET = "BET:";
	const std::string CMD_TIMELEFT = "TIMELEFT:";
	const std::string CMD_TURNEND = "TURNEND:";
	const std::string CMD_MSG_PLAYER = "MSG:";

	const std::string MSG_GAME_FULL = "Could not join, game is full.";
	const std::string MSG_C_CLIENT_EXISTS = "There is already a C client in the game.";
	const std::string MSG_NO_C_CLIENT = "Command will not be processed. There is no C client.";
	const std::string MSG_NAME_TAKEN = "That name is already in use.";
};