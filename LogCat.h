#ifndef _LOGCAT_H_
#define _LOGCAT_H_

#define LOG  1
#define LEVEL	0

#define DEBUG	0
#define INFO	1
#define NOTICE	2
#define ERROR	3

#include <string>
enum LOG_TYPE
{
	LOG_DEBUG,
	LOG_INFO,
	LOG_NOTICE,
	LOG_ERROR
};


#if LOG

#include <android/log.h>

void Debug(const char* tag, const char* msg);
void Info(const char* tag, const char* msg);
void Notice(const char* tag, const char* msg);
void Error(const char* tag, const char* msg);

#endif	// LOG

inline void log(LOG_TYPE type, const char* tag, const char* msg) {
#if LOG
	switch(type){
	case LOG_DEBUG:{
		Debug(tag, msg);
		break;
	}
	case LOG_INFO:{
		Info(tag, msg);
		break;
	}
	case LOG_NOTICE:{
		Notice(tag, msg);
		break;
	}
	case LOG_ERROR:{
		Error(tag, msg);
		break;
	}
	}
#endif
}

#endif	// _LOGCAT_H_
