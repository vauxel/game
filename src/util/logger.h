#pragma once

#include <stdio.h>
#include <time.h>
#include <string.h>

static inline char* timenow();

#define _FILE						strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define PRINTFUNCTION(format, ...)	fprintf(stderr, format, __VA_ARGS__)

#define LOG_LVL_NONE				0x00
#define LOG_LVL_ERROR				0x01
#define LOG_LVL_WARNING				0x02
#define LOG_LVL_INFO				0x03
#define LOG_LVL_DEBUG				0x04

#ifndef LOG_LEVEL
#define LOG_LEVEL					LOG_LVL_DEBUG
#endif

#define LOG_FORMAT					(const char*)"%s | %-7s | %-15s | %s:%d | "
#define LOG_ARGS(LOG_TAG)			timenow(), LOG_TAG, _FILE, __FUNCTION__, __LINE__

#define NEWLINE						"\n"

#define LOG_LVL_ERROR_TAG			"ERROR"
#define LOG_LVL_WARNING_TAG			"WARNING"
#define LOG_LVL_INFO_TAG			"INFO"
#define LOG_LVL_DEBUG_TAG			"DEBUG"

#if LOG_LEVEL >= LOG_LVL_DEBUG
#define LOG_DEBUG(message, args...)		PRINTFUNCTION(LOG_FORMAT message NEWLINE, LOG_ARGS(LOG_LVL_DEBUG_TAG), ## args)
#else
#define LOG_DEBUG(message, args...)
#endif

#if LOG_LEVEL >= LOG_LVL_INFO
#define LOG_INFO(message, args...)		PRINTFUNCTION(LOG_FORMAT message NEWLINE, LOG_ARGS(LOG_LVL_INFO_TAG), ## args)
#else
#define LOG_INFO(message, args...)
#endif

#if LOG_LEVEL >= LOG_LVL_WARNING
#define LOG_WARNING(message, args...)	PRINTFUNCTION(LOG_FORMAT message NEWLINE, LOG_ARGS(LOG_LVL_WARNING_TAG), ## args)
#else
#define LOG_WARNING(message, args...)
#endif

#if LOG_LEVEL >= LOG_LVL_ERROR
#define LOG_ERROR(message, args...)		PRINTFUNCTION(LOG_FORMAT message NEWLINE, LOG_ARGS(LOG_LVL_ERROR_TAG), ## args)
#else
#define LOG_ERROR(message, args...)
#endif

static inline char* timenow() {
	static char buffer[64];
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", timeinfo);
	return buffer;
}
