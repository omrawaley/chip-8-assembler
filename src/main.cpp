#include <iostream>
#include <fstream>
#include <sstream>

#include "ErrorAccumulator.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

int main(int argc, char* argv[])
{
    std::ifstream program(argv[1]);

    std::stringstream buffer;
    buffer << program.rdbuf();

    const std::string& source = buffer.str();

    ErrorAccumulator errorAccumulator;

    Lexer lexer(source, errorAccumulator);

    Parser parser(lexer, errorAccumulator);
    
    std::vector<Token> tokens;

    // while(!lexer.isAtEnd())
    // {
    //     tokens.push_back(lexer.readToken());
    // }

    for(auto& token : tokens)
    {
        std::cout << "Lex: " << token.lexeme << " " << "Type: " << static_cast<int>(token.type) << "\n";
    }

    parser.parseMnemonic(lexer.readToken());

    errorAccumulator.displayErrorsIfAny();

    return 0;
}