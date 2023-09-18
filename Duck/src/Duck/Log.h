#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"
#include "duckpch.h"

namespace Duck {
	class DUCK_API Log{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define DUCK_CORE_TRACE(...)::Duck::Log::GetCoreLogger()->trace(__VA_ARGS__);
#define DUCK_CORE_INFO(...)::Duck::Log::GetCoreLogger()->info(__VA_ARGS__);
#define DUCK_CORE_WARN(...)::Duck::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define DUCK_CORE_ERROR(...)::Duck::Log::GetCoreLogger()->error(__VA_ARGS__);
#define DUCK_CORE_FATAL(...)::Duck::Log::GetCoreLogger()->critical(__VA_ARGS__);

#define DUCK_TRACE(...)::Duck::Log::GetClientLogger()->trace(__VA_ARGS__);
#define DUCK_INFO(...)::Duck::Log::GetClientLogger()->info(__VA_ARGS__);
#define DUCK_WARN(...)::Duck::Log::GetClientLogger()->warn(__VA_ARGS__);
#define DUCK_ERROR(...)::Duck::Log::GetClientLogger()->error(__VA_ARGS__);
#define DUCK_FATAL(...)::Duck::Log::GetClientLogger()->critical(__VA_ARGS__);