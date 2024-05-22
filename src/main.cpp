#include "main.hpp"

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
    {TokenType::Keyword, "Keyword"},
    {TokenType::Identifier, "Identifier"},
    {TokenType::Number, "Number"},
    {TokenType::Operator, "Operator"},
    {TokenType::Punctuation, "Punctuation"},
    {TokenType::EndOfFile, "EndOfFile"}
};

int main (int argc, char** argv) {
    if (argc != 2) {
        std::cout << "Wrong amount of arguments.\n";
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
        std::cout << error << '\n';
        return 1;
    }

    return 0;
}
