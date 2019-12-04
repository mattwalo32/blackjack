#pragma once

#include <string>
#include "../../server/ConnectionConstants.h"

namespace GameConstants {
	// Graphics
	const float ASPECT_RATIO = 412 / 240;
	const int DEFAULT_WINDOW_WIDTH = 1236; // Background image is 412 x 240
	const int DEFAULT_WINDOW_HEIGHT = 720;

	// Connection
	const std::string HOST_NAME = "localhost";
	const std::string CHANNEL = "/socket";
	const int PORT = 9090;

	// Client commands
	const std::string CMD_SET_C_CLIENT = ConnectionConstants::CMD_TYPE + "1";

	// Game
	const int ACE_LOW_VALUE = 1;
	const int ACE_HIGH_VALUE = 11;
	const int NUM_ACE_VALUES = 2;
	const int WINNING_VALUE = 21;
	const int DEALER_HIT_AMOUNT = 17;

	const int NUM_STARTING_CARDS = 2;
	const int DEFAULT_NUM_DECKS = 6;
	const int ROUND_RESET_DELAY_SEC = 3;
	const int TURN_TIME_SECONDS = 20;
	const int TURN_TIME_MILLIS = TURN_TIME_SECONDS * 1000;

	const int STARTING_CASH = 500;
	const int MIN_BET = 20;
	const int MAX_BET = 200;

	std::string getCardFilename(Card card) {

		const int code = std::stoi(card.getCode());

		switch (code) {
			case 0: return "AD";
			case 1: return "AH";
			case 2: return "AS";
			case 3: return "AC";

			case 4: return "2D";
			case 5: return "2H";
			case 6: return "2S";
			case 7: return "2C";

			case 8: return "3D";
			case 9: return "3H";
			case 10: return "3S";
			case 11: return "3C";

			case 12: return "4D";
			case 13: return "4H";
			case 14: return "4S";
			case 15: return "4C";

			case 16: return "5D";
			case 17: return "5H";
			case 18: return "5S";
			case 19: return "5C";

			case 20: return "6D";
			case 21: return "6H";
			case 22: return "6S";
			case 23: return "6C";

			case 24: return "7D";
			case 25: return "7H";
			case 26: return "7S";
			case 27: return "7C";

			case 28: return "8D";
			case 29: return "8H";
			case 30: return "8S";
			case 31: return "8C";

			case 32: return "9D";
			case 33: return "9H";
			case 34: return "9S";
			case 35: return "9C";

			case 36: return "10D";
			case 37: return "10H";
			case 38: return "10S";
			case 39: return "10C";

			case 40: return "JD";
			case 41: return "JH";
			case 42: return "JS";
			case 43: return "JC";

			case 44: return "QD";
			case 45: return "QH";
			case 46: return "QS";
			case 47: return "QC";

			case 48: return "KD";
			case 49: return "KH";
			case 50: return "KS";
			case 51: return "KC";
		}
	}
}