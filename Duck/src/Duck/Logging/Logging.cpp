//---------------------------------------------------------
// File:    Logging.cpp
//authors:	Kimber Ker Soon Kiat
// email:	s.ker\@digipen.edu
// 
//
// Brief:     Contains the definitions related to logging
//
// Copyright © 2023 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "duckpch.h"
#include "Logging.h"

// Console Sink Implementation
void ConsoleSink::Log(const std::string& message, LogLevel level) {
    std::string prefix = GetLogLevelPrefix(level);

    // Define color codes based on log level
    std::string colorCode;
    switch (level) {
    case LogLevel::DEBUG:
        colorCode = ANSI_COLOR_BLUE;
        break;
    case LogLevel::INFO:
        colorCode = ANSI_COLOR_GREEN;
        break;
    case LogLevel::WARNING:
        colorCode = ANSI_COLOR_YELLOW;
        break;
    case LogLevel::ERRORS:
    case LogLevel::CRITICAL:
        colorCode = ANSI_COLOR_RED;
        break;
    default:
        colorCode = ANSI_COLOR_RESET;
    }

    // Reset color after the message
    std::string resetColor = ANSI_COLOR_RESET;

    // Print colored log message
    std::cout << colorCode << "[" << GetCurrentTimeWindow() << "] " << prefix << ": " << message << resetColor << std::endl;
}

// File Sink
FileSink::FileSink() {
    // Create a full path by appending "logs/" to the provided filename
    std::string fullFilePath = "../txtfiles/logs/" + GetCurrentTimeLog() + ".txt";

    file_ = new std::ofstream(fullFilePath, std::ios::app);
    if (!file_->is_open()) {
        std::cerr << "Error: Failed to open log file " << GetCurrentTimeLog() + ".txt" << std::endl;
    }
}

void FileSink::Log(const std::string& message, LogLevel level) {
    if (file_ && file_->is_open()) {
        std::string prefix = GetLogLevelPrefix(level);
        (*file_) << "[" << GetCurrentTimeWindow() << "] " << prefix << ": " << message << std::endl;
    }
}

// Logger Implementation
Logging::Logging(LogLevel level) : level_(level) {}

void Logging::AddSink(LogSink* sink) {
    sinks_.push_back(sink);
}

//void Logging::Log(const std::string& message, LogLevel msgLevel) {
//    if (msgLevel >= level_) {
//        for (auto sink : sinks_) {
//            sink->Log(message, msgLevel);
//        }
//    }
//}

template <typename... Args>
void Logging::Log(LogLevel msgLevel, const Args&... args) {
    if (msgLevel >= level_) {
        std::ostringstream oss;
        // Convert each argument to a string and append to the stream
        ((oss << args), ...);
        std::string message = oss.str();
        for (auto sink : sinks_) {
            sink->Log(message, msgLevel);
        }
    }
}

// Helper Functions
std::string GetLogLevelPrefix(LogLevel level) {
    switch (level) {
    case LogLevel::DEBUG:       return "DEBUG";
    case LogLevel::INFO:        return "INFO";
    case LogLevel::WARNING:     return "WARNING";
    case LogLevel::ERRORS:       return "ERROR";
    case LogLevel::CRITICAL:    return "CRITICAL";
    default:                    return "UNKNOWN";
    }
}

std::string GetCurrentTimeWindow() {
    time_t now = std::time(nullptr);
    struct tm timeInfo;
    localtime_s(&timeInfo, &now); // Use localtime_s for Windows
    std::stringstream ss;
    ss << std::put_time(&timeInfo, "%d-%m-%Y (%H:%M:%S)");
    return ss.str();
}

std::string GetCurrentTimeLog() {
    time_t now = std::time(nullptr);
    struct tm timeInfo;
    localtime_s(&timeInfo, &now); // Use localtime_s for Windows
    std::stringstream ss;
    ss << std::put_time(&timeInfo, "%d-%m-%Y (%H-%M-%S)");
    return ss.str();
}
