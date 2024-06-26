#include "../../include/lexer.hpp"

Lexer::Lexer (std::string &input) { 
    this->input = input;
    this->position = 0;
}

std::vector<Token> Lexer::tokenize () {
    std::vector<Token> tokens;
    while (position < input.size()) {
        char currentChar = input[position];

        if (isComment(currentChar)) {
            skipComment();
            continue;
        }

        if (std::isspace(currentChar)) {
            position++;
            continue;
        }

        if (std::isalpha(currentChar)) {
            tokens.push_back(tokenizeIdentifierOrKeyword());
            continue;
        }

        if (std::isdigit(currentChar)) {
            tokens.push_back(tokenizeNumber());
            continue;
        }

        if (isString(currentChar)) {
            tokens.push_back(tokenizeString());
            continue;
        }

        if (isOperator(currentChar)) {
            tokens.push_back(tokenizeOperator());
            continue;
        }

        if (isPunctuation(currentChar)) {
            tokens.push_back(tokenizePunctuation());
            continue;
        }

        throw std::runtime_error("Unexpected character: " + std::string(1, currentChar));
    }
    tokens.push_back({TokenType::EndOfFile, ""});
    return tokens;
}

bool Lexer::isString (char ch) {
    return ch == '"';
}

bool Lexer::isSingleLineComment (char ch) {
    return ch == '#';
}

bool Lexer::isMultiLineComment (char ch) {
    return ch == '~';
}

bool Lexer::isComment (char ch) {
    return isSingleLineComment(ch) || isMultiLineComment(ch);
}

bool Lexer::isOperator (char ch) {
    return ch == '=' || ch == '+' || ch == '-' || ch == '/' || ch == '*';
}

bool Lexer::isPunctuation (char ch) {
    return ch == ';' || ch == '(' || ch == ')';
}

void Lexer::skipComment () {
    char currentChar = input[position];
    if (isMultiLineComment(currentChar)) {
        position++;
        currentChar = input[position];
        while (position < input.size() && !isMultiLineComment(currentChar)) {
            position++;
            currentChar = input[position];
        }
        position++;
    }
    else {
        position++;
        currentChar = input[position];
        while (position < input.size() && currentChar != '\n') {
            position++;
            currentChar = input[position];
        }
        position++;
    }
}

Token Lexer::tokenizeIdentifierOrKeyword () {
    size_t start = position;
    while (position < input.size() && (std::isalnum(input[position]) || input[position] == '_')) {
        position++;
    }
    std::string value = input.substr(start, position - start);
    if (value == "int" || value == "string") {
        return {TokenType::Type, value};
    }
    else if (value == "print") {
        return {TokenType::Print, value};
    }
    else if (value == "if") {
        return {TokenType::If, value};
    }
    else if (value == "else") {
        return {TokenType::Else, value};
    }
    else  {
        return {TokenType::Identifier, value};
    }
}

Token Lexer::tokenizeNumber () {
    size_t start = position;
    while (position < input.size() && std::isdigit(input[position])) {
        position++;
    }
    std::string value = input.substr(start, position - start);
    return {TokenType::Number, value};
}

Token Lexer::tokenizeOperator () {
    char currentChar = input[position];
    position++;
    return {TokenType::Operator, std::string(1, currentChar)};
}

Token Lexer::tokenizePunctuation () {
    char currentChar = input[position];
    position++;
    return {TokenType::Punctuation, std::string(1, currentChar)};
}

Token Lexer::tokenizeString () {
    position++;
    size_t start = position;
    while (position < input.size() && input[position] != '"') {
        position++;
    }
    if (input[position] != '"') {
        throw std::runtime_error("Missing matching \"." );
    }
    std::string value = input.substr(start, position - start);

    return {TokenType::String, value};
}
