#include "parser.hpp"

Parser::Parser (std::vector<Token> &tokens) {
    this->tokens = tokens;
    this->position = 0;
}

std::shared_ptr<ASTNode> Parser::parse () {
    auto program = std::make_shared<ASTNode>(ASTNodeType::Program);
    while (!isAtEnd()) {
        if (match(TokenType::Keyword)) {
            if (previous().value == "int") {
                program->children.push_back(parseDeclaration());
            } 
            else if (previous().value == "print") {
                program->children.push_back(parsePrint());
            }
        } 
        else {
            throw std::runtime_error("Unexpected token: " + previous().value);
        }
    }
    return program;
}

bool Parser::isAtEnd () {
    return peek().type == TokenType::EndOfFile;
}

Token Parser::peek () {
    return this->tokens[this->position];
}

Token Parser::previous () {
    return this->tokens[this->position - 1];
}

Token Parser::advance () {
    if (!isAtEnd()) {
        this->position++;
    }
    return previous();
}

bool Parser::match (TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

bool Parser::check (TokenType type) {
    if (isAtEnd()) {
        return false;
    }
    return peek().type == type;
}

std::shared_ptr<ASTNode> Parser::parseDeclaration () {
    auto declaration = std::make_shared<ASTNode>(ASTNodeType::Declaration);
    if (!match(TokenType::Identifier)) {
        throw std::runtime_error("Expected identifier after 'int'");
    }
    declaration->value = previous().value;

    if (!match(TokenType::Operator) || previous().value != "=") {
        throw std::runtime_error("Expected '=' after identifier");
    }

    declaration->children.push_back(parseExpression());
    if (!match(TokenType::Punctuation) || previous().value != ";") {
        std::cout << "______\n";
        std::cout << previous().value << "\n";
        std::cout << astNames[declaration->children[0]->type] + " " + declaration->children[0]->value + "\n";
        std::cout << astNames[declaration->type] + " " + declaration->value + "\n";
        throw std::runtime_error("Expected ';' after expression");
    }

    return declaration;
}

std::shared_ptr<ASTNode> Parser::parsePrint () {
    auto printStmt = std::make_shared<ASTNode>(ASTNodeType::Print);
    if (!match(TokenType::Punctuation) || previous().value != "(") {
        throw std::runtime_error("Expected '(' after 'print'");
    }

    printStmt->children.push_back(parseExpression());

    if (!match(TokenType::Punctuation) || previous().value != ")") {
        throw std::runtime_error("Expected ')' after expression");
    }
    if (!match(TokenType::Punctuation) || previous().value != ";") {
        throw std::runtime_error("Expected ';' after ')'");
    }

    return printStmt;
}

std::shared_ptr<ASTNode> Parser::parseExpression () {
    return parseFactor();
}

std::shared_ptr<ASTNode> Parser::parseTerm () {
    auto left = parsePrimary();
    while (check(TokenType::Operator) && (peek().value == "*" || peek().value == "/")) {
        advance();
        auto binaryExpr = std::make_shared<ASTNode>(ASTNodeType::BinaryOperation, previous().value);
        binaryExpr->children.push_back(left);
        binaryExpr->children.push_back(parsePrimary());
        std::cout << astNames[left->type] + " " + left->value + "\n";
        std::cout << astNames[binaryExpr->children[1]->type] + " " + binaryExpr->children[1]->value + "\n";
        left = binaryExpr;
    }
    return left;
}

std::shared_ptr<ASTNode> Parser::parseFactor () {
    auto left = parseTerm();
    while (check(TokenType::Operator) && (peek().value == "+" || peek().value == "-")) {
        advance();
        auto binaryExpr = std::make_shared<ASTNode>(ASTNodeType::BinaryOperation, previous().value);
        binaryExpr->children.push_back(left);
        binaryExpr->children.push_back(parseTerm());
        left = binaryExpr;
    }
    return left;
}

std::shared_ptr<ASTNode> Parser::parsePrimary () {
    if (check(TokenType::Number)) {
        auto numberNode = std::make_shared<ASTNode>(ASTNodeType::Number, peek().value);
        advance();
        return numberNode;
    } 
    else if (check(TokenType::Identifier)) {
        auto identifierNode = std::make_shared<ASTNode>(ASTNodeType::Identifier, peek().value);
        advance();
        return identifierNode;
    } 
    else if (check(TokenType::Punctuation) && peek().value == "(") {
        advance();
        auto exprNode = parseExpression();
        if (!match(TokenType::Punctuation) || previous().value != ")") {
            throw std::runtime_error("Expected ')' after expression");
        }
        return exprNode;
    } 
    else {
        throw std::runtime_error("Expected number, identifier, or '('");
    }
}
