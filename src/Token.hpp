#pragma once

#include <cstdint>
#include <string>

#include "Literals.hpp"

enum class TokenType
{
    Mnemonic,
    Register,
    Hex,
    Label,
    Eof,
    // None,
};

static std::string tokenTypeToString(TokenType type)
{
    std::string string;

    switch(type)
    {
        case TokenType::Mnemonic:
            string = "Mnemonic";
            break;

        case TokenType::Register:
            string = "Register";
            break;

        case TokenType::Hex:
            string = "Hex literal";
            break;

        case TokenType::Label:
            string = "Label";
            break;

        case TokenType::Eof:
            string = "EOF";
            break;
    }

    return string;
}

struct Token
{
    TokenType type;

    std::string lexeme;

    std::variant<Register, std::string> literal;

    int line;

    Token(TokenType type, std::string lexeme, int line) : type{type}, lexeme{lexeme}, line{line}
    {
    }
};