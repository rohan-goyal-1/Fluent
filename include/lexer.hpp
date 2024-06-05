#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "../logger/logger.hpp"

class Lexer {
public:
    Lexer(std::string &input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t position;

    bool isOperator(char ch);

    bool isString(char ch);

    bool isPunctuation(char ch);

    Token tokenizeIdentifierOrKeyword();
    Token tokenizeNumber();
    Token tokenizeOperator();
    Token tokenizePunctuation();
    Token tokenizeString();

    bool isComment(char ch);
    bool isSingleLineComment(char ch);
    bool isMultiLineComment(char ch);
    void skipComment();
};
