#include "Logger.h"
#include <iostream>

HANDLE Logger::hConsole;

/* Init */
void Logger::Init()
{
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}

/* Normal Log */
void Logger::Log(const std::string& msg)
{
	LogColor(msg, LOG_COLOR_DEFAULT);
}

/* Info */
void Logger::LogInfo(const std::string& msg)
{
	LogColor(msg, LOG_COLOR_CYAN);
}

/* Success */
void Logger::LogSuccess(const std::string& msg)
{
	LogColor(msg, LOG_COLOR_GREEN);
}

/* Warning */
void Logger::LogWarning(const std::string& msg)
{
	LogColor(msg, LOG_COLOR_YELLOW);
}

/* Error */
void Logger::LogError(const std::string& msg)
{
	LogColor(msg, LOG_COLOR_RED);
}

/* Fixme */
void Logger::LogFixme(const std::string& msg)
{
	LogColor(msg, LOG_COLOR_PINK);
}

/*
 * INTERNAL
 */

void Logger::LogColor(const std::string& msg, int color)
{
	SetConsoleTextAttribute(hConsole, color);
	std::cout << msg << std::endl;
	SetConsoleTextAttribute(hConsole, LOG_COLOR_DEFAULT);
}
