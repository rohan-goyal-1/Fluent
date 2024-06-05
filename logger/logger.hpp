#pragma once

#include <iostream>
#include <string>
#include <ctime>

#include "../include/ast_node.hpp"
#include "../include/token.hpp"

extern std::map<ASTNodeType, std::string> astNames;
extern std::map<TokenType, std::string> tokenNames;

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static void log (std::string message, LogLevel messageLevel);
    static void log (char message, LogLevel messageLevel);

private:
    static std::string getCurrentTime();
};
