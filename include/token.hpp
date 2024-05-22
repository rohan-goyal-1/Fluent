#pragma once

#include <string>
#include <map>

enum class TokenType {
    Keyword,
    Identifier,
    Number,
    Operator,
    Punctuation,
    EndOfFile
};

extern std::map<TokenType, std::string> tokenNames;

struct Token {
    TokenType type;
    std::string value;
};

