#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "ast_node.hpp"
#include "../logger/logger.hpp"

class Parser {
public:
    Parser(std::vector<Token> &tokens);

    std::shared_ptr<ASTNode> parse();

private:
    std::vector<Token> tokens;
    size_t position;

    bool isAtEnd();
    Token peek();
    Token previous();
    Token advance();
    bool check(TokenType type);

    std::shared_ptr<ASTNode> parseDeclaration();
    std::shared_ptr<ASTNode> parseConditional();
    std::shared_ptr<ASTNode> parsePrint();
    std::shared_ptr<ASTNode> parseExpression();
    std::shared_ptr<ASTNode> parseTerm();
    std::shared_ptr<ASTNode> parseFactor();
    std::shared_ptr<ASTNode> parsePrimary();
};

