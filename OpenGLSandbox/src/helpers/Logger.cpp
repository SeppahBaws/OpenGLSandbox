#include "pch.h"
#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Logger::s_Logger;

void Logger::Init()
{
	spdlog::set_pattern("%^[%T.%e] | %-8l | %v%$");

	s_Logger = spdlog::stdout_color_mt("Logger");
	s_Logger->set_level(spdlog::level::trace);
}
