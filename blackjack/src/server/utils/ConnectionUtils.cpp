#include "ConnectionUtils.h"

/*
 * Checks if the given command starts the the given prefix.
 */
bool ConnectionUtils::cmdHasPrefix(std::string cmd, std::string prefix) {
	return cmd.length() >= prefix.length() &&
		cmd.substr(0, prefix.length()) == prefix;
}