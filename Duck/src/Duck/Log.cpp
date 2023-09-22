#include "duckpch.h"
#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Duck {
	// Initialize the static logger instances
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		// Set the log pattern for both core and client loggers
		spdlog::set_pattern("%^[%T] %n: %v%$");

		// Create and configure the core logger
		s_CoreLogger = spdlog::stdout_color_mt("DUCK");
		s_CoreLogger->set_level(spdlog::level::trace);

		// Create and configure the client logger
		s_ClientLogger = spdlog::stdout_color_mt("App");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}
