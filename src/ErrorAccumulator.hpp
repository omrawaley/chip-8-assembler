#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "Error.hpp"
#include "Token.hpp"

class ErrorAccumulator
{
    private:
        std::vector<Error> errors;

        std::string getErrorInformation(int line, int col)
        {
            return "\n => Error on line " + std::to_string(line) + " column " + std::to_string(col) + ": ";
        }

    public:
        void displayErrorsIfAny()
        {
            if(this->errors.size() == 0)
                return;

            for(auto& error : this->errors)
            {
                std::cerr << error.message << "\n";
            }
        }

        void reportUnexpectedCharacter(char c, int line, int col)
        {
            std::string message = ErrorAccumulator::getErrorInformation(line, col) + "Unexpected character " + c;

            this->errors.push_back(Error(message, line, col));
        }

        void reportUnexpectedMnemonic(std::string string, int line, int col)
        {
            std::string message = ErrorAccumulator::getErrorInformation(line, col) + "Unexpected mnemonic " + string;

            this->errors.push_back(Error(message, line, col));
        }

        void reportUnexpectedOperand(std::string string, TokenType expectedType, TokenType receivedType, int line, int col)
        {
            std::string message = ErrorAccumulator::getErrorInformation(line, col) + "Unexpected operand " + string + ". Expected " + tokenTypeToString(expectedType) + "; Received " + tokenTypeToString(receivedType);

            this->errors.push_back(Error(message, line, col));
        }

        void reportFailedMnemonicParse(std::string string, int line, int col)
        {
            std::string message = ErrorAccumulator::getErrorInformation(line, col) + "Unable to parse mnemonic " + string;

            this->errors.push_back(Error(message, line, col));
        }
};