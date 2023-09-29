//---------------------------------------------------------
// File:    Log.h
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the declarations for logging
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "duckpch.h"

namespace Duck {
	// Logger class for handling application logs
	class Log {
	public:
		// Initialize the logger
		static void Init();

		// Get the core logger instance
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }

		// Get the client logger instance
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		// Static instances of the core and client loggers
		static std::shared_ptr<spdlog::logger> s_CoreLogger;

		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Macros for logging at different levels (core and client)
#define DUCK_CORE_TRACE(...) ::Duck::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define DUCK_CORE_INFO(...) ::Duck::Log::GetCoreLogger()->info(__VA_ARGS__);
#define DUCK_CORE_WARN(...) ::Duck::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define DUCK_CORE_ERROR(...) ::Duck::Log::GetCoreLogger()->error(__VA_ARGS__);
#define DUCK_CORE_CRITICAL(...) ::Duck::Log::GetCoreLogger()->critical(__VA_ARGS__);

#define DUCK_TRACE(...) ::Duck::Log::GetClientLogger()->trace(__VA_ARGS__);
#define DUCK_INFO(...) ::Duck::Log::GetClientLogger()->info(__VA_ARGS__);
#define DUCK_WARN(...) ::Duck::Log::GetClientLogger()->warn(__VA_ARGS__);
#define DUCK_ERROR(...) ::Duck::Log::GetClientLogger()->error(__VA_ARGS__);
#define DUCK_CRITICAL(...) ::Duck::Log::GetClientLogger()->critical(__VA_ARGS__);
