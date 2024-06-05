#include "../../include/parser.hpp"

Parser::Parser (std::vector<Token> &tokens) {
    this->tokens = tokens;
    this->position = 0;
}

std::shared_ptr<ASTNode> Parser::parse () {
    auto program = std::make_shared<ASTNode>(ASTNodeType::Program);
    while (!isAtEnd()) {
        if (check(TokenType::Type)) {
            advance();
            program->children.push_back(parseDeclaration());
        } 
        else if (check(TokenType::Print)) {
            advance();
            program->children.push_back(parsePrint());
        }
        else if (check(TokenType::If)) {
            advance();
            program->children.push_back(parseConditional());
        }
        else {
            throw std::runtime_error("Unexpected token: " + peek().value);
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

bool Parser::check (TokenType type) {
    if (isAtEnd()) {
        return false;
    }
    return peek().type == type;
}

std::shared_ptr<ASTNode> Parser::parseConditional () {
    auto conditional = std::make_shared<ASTNode>(ASTNodeType::Conditional);
    return nullptr;
}

std::shared_ptr<ASTNode> Parser::parseDeclaration () {
    auto declaration = std::make_shared<ASTNode>(ASTNodeType::Declaration);
    if (!check(TokenType::Identifier)) {
        throw std::runtime_error("Expected identifier after " + previous().value);
    }
    declaration->value = peek().value;
    advance();

    if (!check(TokenType::Operator) || peek().value != "=") {
        throw std::runtime_error("Expected '=' after identifier");
    }

    advance();
    declaration->children.push_back(parseExpression());
    if (!check(TokenType::Punctuation) || peek().value != ";") {
        // std::cout << "______\n";
        // std::cout << previous().value << "\n";
        // std::cout << astNames[declaration->children[0]->type] + " " + declaration->children[0]->value + "\n";
        // std::cout << astNames[declaration->type] + " " + declaration->value + "\n";
        throw std::runtime_error("Expected ';' after expression");
    }
    advance();

    return declaration;
}

std::shared_ptr<ASTNode> Parser::parsePrint () {
    auto printStmt = std::make_shared<ASTNode>(ASTNodeType::Print);
    if (!check(TokenType::Punctuation) || peek().value != "(") {
        throw std::runtime_error("Expected '(' after 'print'");
    }

    advance();
    printStmt->children.push_back(parseExpression());

    if (!check(TokenType::Punctuation) || peek().value != ")") {
        throw std::runtime_error("Expected ')' after expression");
    }
    advance();
    if (!check(TokenType::Punctuation) || peek().value != ";") {
        throw std::runtime_error("Expected ';' after ')'");
    }
    advance();

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
        // std::cout << astNames[left->type] + " " + left->value + "\n";
        // std::cout << astNames[binaryExpr->children[1]->type] + " " + binaryExpr->children[1]->value + "\n";
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
        if (!check(TokenType::Punctuation) || peek().value != ")") {
            throw std::runtime_error("Expected ')' after expression");
        }
        advance();
        return exprNode;
    } 
    else {
        throw std::runtime_error("Expected number, identifier, or '('");
    }
}
