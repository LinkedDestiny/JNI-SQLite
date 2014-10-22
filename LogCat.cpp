#include "LogCat.h"

void Debug(const char* tag, const char* msg) {
#if DEBUG >= LEVEL
	__android_log_print(ANDROID_LOG_DEBUG, tag, msg, 0);
#endif
}

void Info(const char* tag, const char* msg) {
#if INFO >= LEVEL
	__android_log_print(ANDROID_LOG_INFO, tag, msg, 0);
#endif
}

void Notice(const char* tag, const char* msg) {
#if NOTICE >= LEVEL
	__android_log_print(ANDROID_LOG_DEBUG, tag, msg, 0);
#endif
}

void Error(const char* tag, const char* msg) {
#if ERROR >= LEVEL
	__android_log_print(ANDROID_LOG_DEBUG, tag, msg, 0);
#endif
}
