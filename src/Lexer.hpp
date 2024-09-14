#pragma once

#include <cstdint>
#include <vector>
#include <optional>
#include <array>

#include "CharacterClasses.hpp"
#include "Token.hpp"
#include "ErrorAccumulator.hpp"

struct SourcePosition
{
    int line, col;

    SourcePosition() : line{1}
    {
    }
};

class Lexer
{
    private:
        SourcePosition sourcePosition;

        ErrorAccumulator& errorAccumulator;

    private:
        const std::string& source;

        int start;
        int current;

        void skipLine()
        {
            while(!this->isAtEnd() && !isNewline(this->peek()))
                this->advance();
        }

        void skipWhitespace()
        {
            while(!this->isAtEnd() && isWhitespace(this->peek()))
                this->advance();
        }

        // Token mnemonic()
        // {
        //     while(isAlphaNumeric(this->peek()))
        //         this->advance();

        //     return this->makeToken(TokenType::Mnemonic);
        // }

        Token mnemonicOrLabel()
        {
            while(isAlphaNumeric(this->peek()))
                this->advance();

            if(isColon(this->peek()))
            {
                Token value = this->makeToken(TokenType::Label);

                this->advance();

                return value;
            }
            else
                return this->makeToken(TokenType::Mnemonic);
        }

        Token operand(TokenType type)
        {
            while(isDecimalDigit(this->peek()))
                this->advance();

            return this->makeToken(type);
        }

        // Token label()
        // {
        //     this->start = this->current;

        //     while(isAlphaNumeric(this->peek()))
        //         this->advance();

        //     return this->makeToken(TokenType::Label);
        // }

        char peek() const
        {
            if(this->isAtEnd())
                return '\0';

            return this->source.at(this->current);
        }

        char advance()
        {
            ++this->sourcePosition.col;

            char result = this->peek();

            ++this->current;

            return result;
        }

        Token makeToken(TokenType type)
        {
            std::string text(this->source.c_str() + this->start, this->source.c_str() + this->current);

            return Token(type, text, this->sourcePosition.line);
        }

    public:
        Lexer(const std::string& source, ErrorAccumulator& errorAccumulator) : source{source}, errorAccumulator{errorAccumulator}
        {
        }

        bool isAtEnd() const
        {
            return this->current >= this->source.length();
        }

        SourcePosition& getSourcePosition()
        {
            return this->sourcePosition;
        }

        Token readToken()
        {
            this->start = this->current;

            char c = this->advance();

            if(isWhitespace(c))
                this->skipWhitespace();

            else if(isNewline(c))
            {
                ++this->sourcePosition.line;
                this->sourcePosition.col = 0;
            }

            else if(isSemicolon(c))
                this->skipLine();

            // else if(isColon(c))
            //     return this->label();

            else if(isPercentageSign(c))
                return this->operand(TokenType::Register);

            else if(isDollarSign(c))
                return this->operand(TokenType::Hex);

            else if(isLetter(c))
                return this->mnemonicOrLabel();

            else
                this->errorAccumulator.reportUnexpectedCharacter(c, this->sourcePosition.line, this->sourcePosition.col);

            if(this->isAtEnd())
                return Token(TokenType::Eof, "End of File.", 0);
            else
                return this->readToken();
        }
};