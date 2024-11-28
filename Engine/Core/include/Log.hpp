#pragma once

#include <fstream>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <unordered_map>

#include "async.hpp"

#ifdef _WIN32
#include <windows.h>
#undef ERROR
#endif

class Logger
{
   public:
    enum class LogLevel { INFO, WARNING, ERROR, DEBUG };

    static Logger& getInstance()
    {
        static Logger instance;
        return instance;
    }

    void setLogFile(const std::string& filename)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (logFile_.is_open()) {
            logFile_.close();
        }
        logFile_.open(filename, std::ios::out | std::ios::app);
    }

    void log(LogLevel level, const std::string& message)
    {
        std::lock_guard<std::mutex> lock(mutex_);

        std::ostringstream oss;
        oss << getLevelString(level) << ": " << message << std::endl;
        std::string formattedMessage = oss.str();

        // Console Output
        setConsoleColor(level);
        std::cout << formattedMessage;
        resetConsoleColor();

        // File Output
        if (logFile_.is_open()) {
            logFile_ << formattedMessage;
        }
    }

    void info(const std::string& message)
    {
        log(LogLevel::INFO, message);
    }
    void warning(const std::string& message)
    {
        log(LogLevel::WARNING, message);
    }
    void error(const std::string& message)
    {
        log(LogLevel::ERROR, message);
    }
    void debug(const std::string& message)
    {
        log(LogLevel::DEBUG, message);
    }

   private:
    std::ofstream logFile_;
    std::mutex mutex_;

    Logger() = default;

    std::string getLevelString(LogLevel level) const
    {
        switch (level) {
            case LogLevel::INFO:
                return "[INFO]";
            case LogLevel::WARNING:
                return "[WARNING]";
            case LogLevel::ERROR:
                return "[ERROR]";
            case LogLevel::DEBUG:
                return "[DEBUG]";
            default:
                return "[UNKNOWN]";
        }
    }

    void setConsoleColor(LogLevel level)
    {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        switch (level) {
            case LogLevel::INFO:
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);
                break;
            case LogLevel::WARNING:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                break;
            case LogLevel::ERROR:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                break;
            case LogLevel::DEBUG:
                SetConsoleTextAttribute(hConsole,
                                        FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
                break;
        }
#else
        switch (level) {
            case LogLevel::INFO:
                std::cout << "\033[32m";
                break;  // Green
            case LogLevel::WARNING:
                std::cout << "\033[33m";
                break;  // Yellow
            case LogLevel::ERROR:
                std::cout << "\033[31m";
                break;  // Red
            case LogLevel::DEBUG:
                std::cout << "\033[36m";
                break;  // Cyan
        }
#endif
    }

    void resetConsoleColor()
    {
#ifdef _WIN32
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
#else
        std::cout << "\033[0m";
#endif
    }
};
