#include "../include/main.hpp"

std::map<ASTNodeType, std::string> astNames = {
    {ASTNodeType::Program, "Program"},
    {ASTNodeType::Declaration, "Declaration"},
    {ASTNodeType::Assignment, "Assignment"},
    {ASTNodeType::Print, "Print"},
    {ASTNodeType::BinaryExpression, "BinaryExpression"},
    {ASTNodeType::Identifier, "Identifier"},
    {ASTNodeType::Number, "Number"},
    {ASTNodeType::BinaryOperation, "BinaryOperation"}
};

std::map<TokenType, std::string> tokenNames = {
    {TokenType::Type, "Type"},
    {TokenType::Print, "Print"},
    {TokenType::Identifier, "Identifier"},
    {TokenType::Number, "Number"},
    {TokenType::String, "String"},
    {TokenType::Operator, "Operator"},
    {TokenType::Punctuation, "Punctuation"},
    {TokenType::EndOfFile, "EndOfFile"},
    {TokenType::If, "If"},
    {TokenType::Else, "Else"}
};

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Wrong amount of arguments.\n";
        return 1;
    }

    std::string lines = "";
    std::string line = "";

    std::ifstream file;
    file.open(argv[1]);
    while (std::getline(file, line)) {
        lines += line + '\n';
    }

    Interpreter interpreter(lines);

    try {
        interpreter.interpret();
    }
    catch (std::string error) {
        std::cerr << error << '\n';
        return 1;
    }

    return 0;
}
