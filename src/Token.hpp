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