#pragma once

#include <string>
#include <map>

enum class TokenType {
    Type,
    Print,
    Identifier,
    Number,
    String,
    Operator,
    Punctuation,
    EndOfFile,
    If,
    Else
};

extern std::map<TokenType, std::string> tokenNames;

struct Token {
    TokenType type;
    std::string value;
};

