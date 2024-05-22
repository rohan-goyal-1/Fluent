#pragma once

#include <string>
#include <vector>

enum class ASTNodeType {
    Program,
    Declaration,
    Assignment,
    Print,
    BinaryExpression,
    Identifier,
    Number,
    BinaryOperation
};

extern std::map<ASTNodeType, std::string> astNames;

struct ASTNode {
    ASTNodeType type;
    std::string value;
    std::vector<std::shared_ptr<ASTNode>> children;

    ASTNode(ASTNodeType type, const std::string& value = "") {
        this->type = type;
        this->value = value;
    }
};

