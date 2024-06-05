#include "logger.hpp"

void Logger::log (std::string message, LogLevel messageLevel) {
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
void Logger::log (char message, LogLevel messageLevel) {
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

std::string Logger::getCurrentTime() {
    time_t now = time(0);
    struct tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);
    return std::string(buffer);
}
