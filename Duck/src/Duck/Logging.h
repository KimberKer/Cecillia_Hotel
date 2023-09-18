#ifndef LOGGING_H
#define LOGGING_H

#include <string>
#include <vector>
#include <iosfwd>  // Include this for forward declaration

// ANSI escape code for text color
// https://talyian.github.io/ansicolors/
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_RESET    "\x1b[0m"

// Log levels
enum class LogLevel {
    DEBUG,      // Blue
    INFO,       // Green
    WARNING,    // Yellow
    ERROR,      // Red
    CRITICAL    // Red
};

// Base LogSink class
class LogSink {
public:
    virtual void Log(const std::string& message, LogLevel level) = 0;
};

// Console Sink
class ConsoleSink : public LogSink {
public:
    void Log(const std::string& message, LogLevel level) override;
};

// File Sink
class FileSink : public LogSink {
public:
    FileSink();
    void Log(const std::string& message, LogLevel level) override;

private:
    std::ofstream* file_; // Use a pointer to std::ofstream
};

// Logging class
class Logging {
public:
    Logging(LogLevel level);
    void AddSink(LogSink* sink);
    void Log(const std::string& message, LogLevel msgLevel);

private:
    LogLevel level_;
    std::vector<LogSink*> sinks_;
};

// Helper Functions
std::string GetCurrentTime();
std::string GetCurrentTimeLog();
std::string GetLogLevelPrefix(LogLevel level);

#endif
