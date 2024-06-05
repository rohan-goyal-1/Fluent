#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>

#include "token.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "ast_node.hpp"
#include "../logger/logger.hpp"

class Interpreter {
private:
    std::string lines;
    std::unordered_map<std::string, int> symbols;
    void executeStatement(std::shared_ptr<ASTNode>& node);
    void executeDeclaration(std::shared_ptr<ASTNode>& node);
    void executePrint(std::shared_ptr<ASTNode>& node);
    int evaluateExpression(std::shared_ptr<ASTNode>& node);
    int evaluateBinaryOperation(std::shared_ptr<ASTNode>& node);

public:
    Interpreter(std::string lines);
    void interpret();
    void executeProgram(std::shared_ptr<ASTNode>& node);
};
