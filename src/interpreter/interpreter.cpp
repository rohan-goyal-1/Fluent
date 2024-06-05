#include "../../include/interpreter.hpp"

Interpreter::Interpreter (std::string lines) {
    this->lines = lines;
}

void printAST (std::shared_ptr<ASTNode>& node, int indent) {
    for (int i = 0; i < indent; ++i) std::cout << "  ";
    std::cout << "Node(Type: " << astNames[node->type] << ", Value: \"" << node->value << "\")\n";
    for (auto& child : node->children) {
        printAST(child, indent + 1);
    }
}

void Interpreter::interpret () {
    Lexer lexer(this->lines);
    std::vector<Token> tokens = lexer.tokenize();
    std::cout << "Tokens:\n___________________\n" << '\n';
    for (Token t : tokens) {
        std::cout << "[" + tokenNames[t.type] + ": " + t.value + "]\n";
    }
    std::cout << '\n';

    Parser parser(tokens);
    std::shared_ptr<ASTNode> ast = parser.parse();
    std::cout << "AST:\n___________________\n" << '\n';
    printAST(ast, 0);
    std::cout << '\n';

    std::cout << "Output: \n";
    executeProgram(ast);
} 

void Interpreter::executeProgram (std::shared_ptr<ASTNode>& node) {
    switch (node->type) {
        case ASTNodeType::Program:
            for (auto& child : node->children) {
                executeStatement(child);
            }
            break;
        default:
            throw std::runtime_error("Expected a Program node");
    }
}
void Interpreter::executeStatement (std::shared_ptr<ASTNode>& node) {
    switch (node->type) {
        case ASTNodeType::Declaration:
            executeDeclaration(node);
            break;
        case ASTNodeType::Print:
            executePrint(node);
            break;
        default:
            throw std::runtime_error("Unexpected AST node type for statement execution");
    }
}

void Interpreter::executeDeclaration (std::shared_ptr<ASTNode>& node) {
    if (node->children.size() != 1) throw std::runtime_error("Invalid declaration node");
    if (node->children[0]->type != ASTNodeType::BinaryOperation &&
        node->children[0]->type != ASTNodeType::Number &&
        node->children[0]->type != ASTNodeType::Identifier) {
        throw std::runtime_error("Invalid expression in declaration");
    }

    auto identifier = node->value;
    auto value = evaluateExpression(node->children[0]);
    symbols[identifier] = value;
}

void Interpreter::executePrint (std::shared_ptr<ASTNode>& node) {
    if (node->children.size() != 1) throw std::runtime_error("Invalid print node");
    std::cout << evaluateExpression(node->children[0]) << std::endl;
}

int Interpreter::evaluateExpression (std::shared_ptr<ASTNode>& node) {
    switch (node->type) {
        case ASTNodeType::Number:
            return std::stoi(node->value);
        case ASTNodeType::Identifier:
            if (symbols.find(node->value) == symbols.end())
                throw std::runtime_error("Undefined variable: " + node->value);
            return symbols[node->value];
        case ASTNodeType::BinaryOperation:
            return evaluateBinaryOperation(node);
        default:
            throw std::runtime_error("Unexpected AST node type for expression evaluation");
    }
}

int Interpreter::evaluateBinaryOperation (std::shared_ptr<ASTNode>& node) {
    if (node->children.size() != 2) throw std::runtime_error("Invalid binary operation node");
    auto left = evaluateExpression(node->children[0]);
    auto right = evaluateExpression(node->children[1]);
    auto& op = node->value;
    
    if (op == "+") return left + right;
    if (op == "-") return left - right;
    if (op == "*") return left * right;
    if (op == "/") {
        if (right == 0) throw std::runtime_error("Division by zero");
        return left / right;
    }
    
    throw std::runtime_error("Unknown binary operator: " + op);
}
