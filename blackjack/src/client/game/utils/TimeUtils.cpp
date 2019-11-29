#include "TimeUtils.h"

unsigned __int64 TimeUtils::systemTimeMillis() {
	return std::chrono::duration_cast<std::chrono::milliseconds>
		(std::chrono::system_clock::now().time_since_epoch()).count();
}