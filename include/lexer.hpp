#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "token.hpp"

class Lexer {
public:
    Lexer(std::string &input);
    std::vector<Token> tokenize();

private:
    std::string input;
    size_t position;

    bool isOperator(char ch);

    bool isPunctuation(char ch);

    Token tokenizeIdentifierOrKeyword();
    Token tokenizeNumber();
    Token tokenizeOperator();
    Token tokenizePunctuation();

    bool isComment(char ch);
    bool isSingleLineComment(char ch);
    bool isMultiLineComment(char ch);
    void skipComment();
};
