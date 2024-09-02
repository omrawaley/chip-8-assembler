// Copyright 2024 Om Rawaley (@omrawaley)

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>
#include <regex>

enum class Opcode : uint8_t
{
    _00E0,
    _00EE,
    _1NNN,
    _2NNN,
    _3XNN,
    _4XNN,
    _5XY0,
    _6XNN,
    _7XNN,
    _8XY0,
    _8XY1,
    _8XY2,
    _8XY3,
    _8XY4,
    _8XY5,
    _8XY6,
    _8XY7,
    _8XYE,
    _9XY0,
    _ANNN,
    _BNNN,
    _CXNN,
    _DXYN,
    _EX9E,
    _EXA1,
    _FX07,
    _FX0A,
    _FX15,
    _FX18,
    _FX1E,
    _FX29,
    _FX33,
    _FX55,
    _FX65,
};

const std::unordered_map<std::string, Opcode> instructions =
{
    {"CLS", Opcode::_00E0},
    {"RET", Opcode::_00EE},
    {"JMP", Opcode::_1NNN},
    {"CALL", Opcode::_2NNN},
    {"SERB", Opcode::_3XNN},
    {"SNERB", Opcode::_4XNN},
    {"SERR", Opcode::_5XY0},
    {"LDRB", Opcode::_6XNN},
    {"ADDRB", Opcode::_7XNN},
    {"LDRR", Opcode::_8XY0},
    {"OR", Opcode::_8XY1},
    {"AND", Opcode::_8XY2},
    {"XOR", Opcode::_8XY3},
    {"ADDRR", Opcode::_8XY4},
    {"SUBRR", Opcode::_8XY5},
    {"SHR", Opcode::_8XY6},
    {"SUBNRR", Opcode::_8XY7},
    {"SHL", Opcode::_8XYE},
    {"SNERR", Opcode::_9XY0},
    {"LDI", Opcode::_ANNN},
    {"JMP0", Opcode::_BNNN},
    {"RND", Opcode::_CXNN},
    {"DRW", Opcode::_DXYN},
    {"SKP", Opcode::_EX9E},
    {"SKNP", Opcode::_EXA1},
    {"LDRDT", Opcode::_FX07},
    {"LDRK", Opcode::_FX0A},
    {"LDDTR", Opcode::_FX15},
    {"LDSTR", Opcode::_FX18},
    {"ADDIR", Opcode::_FX1E},
    {"LDFR", Opcode::_FX29},
    {"LDBR", Opcode::_FX33},
    {"LDMIR", Opcode::_FX55},
    {"LDRMI", Opcode::_FX65}
};

std::unordered_map<std::string, uint16_t> labels;

std::vector<std::string> getTokens(std::string line)
{
    std::vector<std::string> tokens;
    std::string token;

    std::stringstream stream(line);
    while(stream >> token)
    {
        tokens.push_back(token);
    }

    return tokens;
}

void collectLabels(std::stringstream& program)
{
    uint16_t address = 0x200;

    std::string line;
    while(std::getline(program, line))
    {
        if(line.empty() || line.at(0) == ';' || line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == ' ')
            continue;

        std::vector<std::string> tokens = getTokens(line);

        if(line.at(0) == '.')
        {
            labels.insert(std::make_pair(tokens.at(0).substr(1), address));
        }
        else
        {
            address += 2;
        }
    }
}

std::string replaceText(const std::string& input, const std::string& find, const std::string& replace)
{
    std::string result = std::regex_replace(input, std::regex("\\b" + find + "\\b"), replace);

    return result;
}

void preprocessProgram(std::stringstream& program)
{
    std::string content = program.str();
    std::istringstream stream(content);

    bool modified = false;

    std::string line;
    while(std::getline(program, line))
    {
        if(line.empty() || line.at(0) == ';' || line.at(0) == '.' || line.at(0) == '\n' || line.at(0) == ' ')
            continue;

        std::vector<std::string> tokens = getTokens(line);

        if(line.at(0) == '#')
        {
            content = replaceText(content, tokens.at(0).substr(1), tokens.at(1));

            modified = true;
        }
    }

    if(modified)
    {
        program.str(content);
        program.clear();
    }
}

std::string assembleLine(std::string line)
{
    std::basic_string<uint8_t> bytes;

    for(size_t i = 0; i < line.length(); i += 2)
    {
        uint16_t byte;

        std::string nextByte = line.substr(i, 2);

        std::istringstream(nextByte) >> std::hex >> byte;

        bytes.push_back(static_cast<uint8_t>(byte));
    }
    
    return std::string(std::begin(bytes), std::end(bytes));
}

std::string parseLine(std::string line, std::stringstream& program, std::streampos oldPos)
{
    std::vector<std::string> tokens = getTokens(line);

    std::stringstream parsedLine;

    switch(instructions.at(tokens.at(0)))
    {
        case Opcode::_00E0:
            parsedLine << "00E0";
            break;

        case Opcode::_00EE:
            parsedLine << "00EE";
            break;

        case Opcode::_1NNN:
            if(labels.find(tokens.at(1)) != labels.end())
            {
                parsedLine << "1" << std::hex << labels.at(tokens.at(1));
                break;
            }

            parsedLine << "1" << tokens.at(1);
            break;

        case Opcode::_2NNN:
            parsedLine << "2" << tokens.at(1);
            break;

        case Opcode::_3XNN:
            parsedLine << "3" << tokens.at(1) << tokens.at(2);
            break;

        case Opcode::_4XNN:
            parsedLine << "4" << tokens.at(1) << tokens.at(2);
            break;

        case Opcode::_5XY0:
            parsedLine << "5" << tokens.at(1) << tokens.at(2) << "0";
            break;

        case Opcode::_6XNN:
            parsedLine << "6" << tokens.at(1) << tokens.at(2);
            break;

        case Opcode::_7XNN:
            parsedLine << "7" << tokens.at(1) << tokens.at(2);
            break;

        case Opcode::_8XY0:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "0";
            break;

        case Opcode::_8XY1:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "1";
            break;

        case Opcode::_8XY2:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "2";
            break;

        case Opcode::_8XY3:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "3";
            break;

        case Opcode::_8XY4:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "4";
            break;

        case Opcode::_8XY5:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "5";
            break;

        case Opcode::_8XY6:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "6";
            break;

        case Opcode::_8XY7:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "7";
            break;

        case Opcode::_8XYE:
            parsedLine << "8" << tokens.at(1) << tokens.at(2) << "E";
            break;

        case Opcode::_9XY0:
            parsedLine << "9" << tokens.at(1) << tokens.at(2) << "0";
            break;

        case Opcode::_ANNN:
            parsedLine << "A" << tokens.at(1);
            break;

        case Opcode::_BNNN:
            parsedLine << "B" << tokens.at(1);
            break;

        case Opcode::_CXNN:
            parsedLine << "C" << tokens.at(1) << tokens.at(2);
            break;

        case Opcode::_DXYN:
            parsedLine << "D" << tokens.at(1) << tokens.at(2) << tokens.at(3);
            break;

        case Opcode::_EX9E:
            parsedLine << "E" << tokens.at(1) << "9E";
            break;

        case Opcode::_EXA1:
            parsedLine << "E" << tokens.at(1) << "A1";
            break;

        case Opcode::_FX07:
            parsedLine << "F" << tokens.at(1) << "07";
            break;

        case Opcode::_FX0A:
            parsedLine << "F" << tokens.at(1) << "0A";
            break;

        case Opcode::_FX15:
            parsedLine << "F" << tokens.at(1) << "15";
            break;

        case Opcode::_FX18:
            parsedLine << "F" << tokens.at(1) << "18";
            break;

        case Opcode::_FX1E:
            parsedLine << "F" << tokens.at(1) << "1E";
            break;

        case Opcode::_FX29:
            parsedLine << "F" << tokens.at(1) << "29";
            break;

        case Opcode::_FX33:
            parsedLine << "F" << tokens.at(1) << "33";
            break;

        case Opcode::_FX55:
            parsedLine << "F" << tokens.at(1) << "55";
            break;

        case Opcode::_FX65:
            parsedLine << "F" << tokens.at(1) << "65";
            break;
    }

    return parsedLine.str();
}

int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        std::cerr << "Error: no arguments provided." << std::endl;
        return 1;
    }

    std::ifstream asmProgram(argv[1], std::ios::in);

    std::stringstream programBuffer;
    programBuffer << asmProgram.rdbuf();

    asmProgram.close();

    preprocessProgram(programBuffer);

    collectLabels(programBuffer);

    programBuffer.clear();
    programBuffer.seekg(0);

    std::ofstream binProgram(argv[2], std::ios::out | std::ios::binary);

    std::string line;
    while(std::getline(programBuffer, line))
    {
        if(line.empty() || line.at(0) == ';' || line.at(0) == '.' || line.at(0) == '#' || line.at(0) == '\n' || line.at(0) == ' ')
            continue;

        std::string parsedLine = parseLine(line, programBuffer, programBuffer.tellg());
        std::string assembledLine = assembleLine(parsedLine);

        binProgram << assembledLine;
    }

    binProgram.close();

    return 0;
}
