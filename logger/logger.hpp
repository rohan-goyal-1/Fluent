#pragma once

#include <iostream>
#include <string>
#include <ctime>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static void log (std::string message, LogLevel messageLevel) {
        std::cout << getCurrentTime() << " ";

        switch (messageLevel) {
            case LogLevel::INFO:
                std::cout << "[INFO] ";
                break;
            case LogLevel::WARNING:
                std::cout << "[WARNING] ";
                break;
            case LogLevel::ERROR:
                std::cout << "[ERROR] ";
                break;
        }

        std::cout << message << '\n';
    }
    static void log (char message, LogLevel messageLevel) {
        std::cout << getCurrentTime() << " ";

        switch (messageLevel) {
            case LogLevel::INFO:
                std::cout << "[INFO] ";
                break;
            case LogLevel::WARNING:
                std::cout << "[WARNING] ";
                break;
            case LogLevel::ERROR:
                std::cout << "[ERROR] ";
                break;
        }

        std::cout << message << '\n';
    }

private:
    static std::string getCurrentTime() {
        time_t now = time(0);
        struct tm* timeinfo = localtime(&now);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
        return std::string(buffer);
    }
};
