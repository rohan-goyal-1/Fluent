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

struct Token {
    TokenType type;
    std::string value;
};

