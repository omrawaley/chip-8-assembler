#pragma once

constexpr bool isWhitespace(char c)
{
    return (c == ' ') || (c == '\r') || (c == '\t');
}

constexpr bool isNewline(char c)
{
    return c == '\n';
}

constexpr bool isPercentageSign(char c)
{
    return c == '%';
}

constexpr bool isDollarSign(char c)
{
    return c == '$';
}

constexpr bool isSemicolon(char c)
{
    return c == ';';
}

constexpr bool isColon(char c)
{
    return c == ':';
}

constexpr bool isLowerAlpha(char c)
{
    return ((c >= 'a') && (c <= 'z'));
}

constexpr bool isUpperAlpha(char c)
{
    return ((c >= 'A') && (c <= 'Z'));
}

constexpr bool isLetter(char c)
{
    return isLowerAlpha(c) || isUpperAlpha(c);
}

constexpr bool isDecimalDigit(char c)
{
    return (c >= '0') && (c <= '9');
}

constexpr bool isAlphaNumeric(char c)
{
    return isLetter(c) || isDecimalDigit(c);
}