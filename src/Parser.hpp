#pragma once

#include <cstdint>
#include <vector>
#include <unordered_map>
#include <fstream>

#include "ErrorAccumulator.hpp"
#include "Lexer.hpp"
#include "Mnemonics.hpp"

class Parser
{
    private:
        ErrorAccumulator& errorAccumulator;

        Lexer& lexer;

        // std::ofstream binary;    // THIS LINE CAUSES THE LEXER TO SKIP THE FIRST CHARACTER FOR SOME REASON

    public:
        Parser(Lexer& lexer, ErrorAccumulator& errorAccumulator) : lexer{lexer}, errorAccumulator{errorAccumulator}
        {
        }

        void parseMnemonic(Token token)
        {
            SourcePosition& sourcePosition = this->lexer.getSourcePosition();

            if(token.type != TokenType::Mnemonic)
                errorAccumulator.reportUnexpectedMnemonic(token.lexeme, sourcePosition.line, sourcePosition.col);

            Mnemonic mnemonic = mnemonicTable.at(token.lexeme);

            std::vector<Token> operandTokens;

            for(size_t i = 0; i < static_cast<uint8_t>(mnemonic.operandCount); ++i)
            {
                operandTokens.push_back(this->lexer.readToken());

                if(mnemonic.operandTypes.at(i) != operandTokens.at(i).type)
                    this->errorAccumulator.reportUnexpectedOperand(operandTokens.at(i).lexeme, mnemonic.operandTypes.at(i), operandTokens.at(i).type, sourcePosition.line, sourcePosition.col);
            }

            switch(mnemonic.instruction)
            {
                case Instruction::CLS:
                    break;

                case Instruction::RET:
                    break;

                case Instruction::LDRB:
                    break;
            }
        }
};