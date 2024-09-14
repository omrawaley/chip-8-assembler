#pragma once

#include <cstdint>
#include <string>

struct Error
{
    std::string message;

    int line;
    int col;

    Error(std::string message) : message{message}
    {
    }

    Error(std::string message, int line, int col) : message{message}, line{line}, col{col}
    {
    }
};