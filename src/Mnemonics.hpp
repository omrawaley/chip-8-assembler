#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

#include "Opcode.hpp"

enum class Instruction
{
    // CLS,
    // RET,
    // JP,
    // CALL,
    // SE,
    // SNE,
    // LD,
    // ADD,
    // OR,
    // AND,
    // XOR,
    // SUB,
    // SHR,
    // SUBN,
    // SHL,
    // RND,
    // DRW,
    // SKP,
    // SKNP,
    CLS,
    RET,
    JP, 
    CALL,
    SERB,
    SNERB,
    SERR,
    LDRB,
    ADDRB,
    LDRR,
    OR,
    AND,
    XOR,
    ADDRR,
    SUBRR,
    SHR,
    SUBNRR,
    SHL,
    SNERR,
    LDI,
    JPO,
    RND,
    DRW,
    SKP,
    SKNP,
    LDRDT,
    LDRK,
    LDDTR,
    LDSTR,
    ADDIR,
    LDFR,
    LDBR,
    LDMIR,
    LDRMI,
};

enum class OperandCount
{
    None,
    One,
    Two,
    Three,
};

struct Mnemonic
{
    Instruction instruction;

    OperandCount operandCount;

    std::vector<TokenType> operandTypes;

    Mnemonic(Instruction instruction, OperandCount operandCount, std::array<std::optional<TokenType>, 3> operandTypes = {std::nullopt, std::nullopt, std::nullopt}) : instruction{instruction}, operandCount{operandCount}
    {
        for(size_t i = 0; i < static_cast<uint8_t>(operandCount); ++i)
        {
            if(operandTypes.at(i).has_value())
                this->operandTypes.push_back(operandTypes.at(i).value());
        }
    }
};

std::unordered_map<std::string, Mnemonic> mnemonicTable
{
    // {"CLS", Instruction::CLS},
    // {"RET", Instruction::RET},
    // {"JP", Instruction::JP},
    // {"CALL", Instruction::CALL},
    // {"SE", Instruction::SE},
    // {"SNE", Instruction::SNE},
    // {"LD", Instruction::LD},
    // {"ADD", Instruction::ADD},
    // {"XOR", Instruction::XOR},
    // {"SUB", Instruction::SUB},
    // {"SHR", Instruction::SHR},
    // {"SUBN", Instruction::SUBN},
    // {"SHL", Instruction::SHL},
    // {"RND", Instruction::RND},
    // {"DRW", Instruction::DRW},
    // {"SKP", Instruction::SKP},
    // {"SKNP", Instruction::SKNP},
    // {"CLS", Mnemonic(Instruction::CLS, OperandCount::None, TokenType::None)},
    // {"RET", Mnemonic(Instruction::RET, OperandCount::None, TokenType::None)},
    // {"JP", Mnemonic(Instruction::JP, OperandCount::One, TokenType::Register, )},
    // {"CALL", Mnemonic(Instruction::CALL, OperandCount::One)},
    // {"SE", Mnemonic(Instruction::SE, OperandCount::Two)},
    // {"SNE", Mnemonic(Instruction::SNE, OperandCount::Two)},
    // {"LD", Mnemonic(Instruction::SNE, OperandCount::Two)},
    // {"ADD", Mnemonic(Instruction::ADD, OperandCount::Two)},
    // {"XOR", Mnemonic(Instruction::XOR, OperandCount::Two)},
    // {"SUB", Mnemonic(Instruction::SUB, OperandCount::Two)},
    // {"SHR", Mnemonic(Instruction::SHR, OperandCount::One)},
    // {"SUBN", Mnemonic(Instruction::SUBN, OperandCount::Two)},
    // {"SHL", Mnemonic(Instruction::SHL, OperandCount::One)},
    // {"RND", Mnemonic(Instruction::RND, OperandCount::One)},
    // {"DRW", Mnemonic(Instruction::DRW, OperandCount::Three)},
    // {"SKP", Mnemonic(Instruction::SKP, OperandCount::One)},
    // {"SKNP", Mnemonic(Instruction::SKNP, OperandCount::One)},
    {"CLS", Mnemonic(Instruction::CLS, OperandCount::None)},
    {"RET", Mnemonic(Instruction::RET, OperandCount::None)},
    {"JP", Mnemonic(Instruction::JP, OperandCount::One, {TokenType::Label})},
    {"CALL", Mnemonic(Instruction::CALL, OperandCount::One, {TokenType::Hex})},
    {"SERB", Mnemonic(Instruction::SERB, OperandCount::Two, {TokenType::Register, TokenType::Hex})},
    {"SNERB", Mnemonic(Instruction::SNERB, OperandCount::Two, {TokenType::Register, TokenType::Hex})},
    {"SERR", Mnemonic(Instruction::SERR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"LDRB", Mnemonic(Instruction::LDRB, OperandCount::Two, {TokenType::Register, TokenType::Hex})},
    {"ADDRB", Mnemonic(Instruction::ADDRB, OperandCount::Two, {TokenType::Register, TokenType::Hex})},
    {"LDRR", Mnemonic(Instruction::LDRR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"OR", Mnemonic(Instruction::OR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"AND", Mnemonic(Instruction::AND, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"XOR", Mnemonic(Instruction::XOR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"ADDRR", Mnemonic(Instruction::ADDRR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"SUBRR", Mnemonic(Instruction::SUBRR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"SHR", Mnemonic(Instruction::ADDRR, OperandCount::One, {TokenType::Register})},
    {"SUBNRR", Mnemonic(Instruction::SUBNRR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"SHL", Mnemonic(Instruction::SHL, OperandCount::One, {TokenType::Register})},
    {"SNERR", Mnemonic(Instruction::SNERR, OperandCount::Two, {TokenType::Register, TokenType::Register})},
    {"LDI", Mnemonic(Instruction::LDI, OperandCount::One, {TokenType::Hex})},
    {"JPO", Mnemonic(Instruction::JPO, OperandCount::One, {TokenType::Label})},
    {"RND", Mnemonic(Instruction::RND, OperandCount::Two, {TokenType::Register, TokenType::Hex})},
    {"DRW", Mnemonic(Instruction::DRW, OperandCount::Three, {TokenType::Register, TokenType::Register, TokenType::Hex})},
    {"SKP", Mnemonic(Instruction::SKP, OperandCount::One, {TokenType::Hex})},
    {"SKNP", Mnemonic(Instruction::SKNP, OperandCount::One, {TokenType::Hex})},
    {"LDRDT", Mnemonic(Instruction::LDRDT, OperandCount::One, {TokenType::Register})},
    {"LDRK", Mnemonic(Instruction::LDRK, OperandCount::One, {TokenType::Register})},
    {"LDDTR", Mnemonic(Instruction::LDDTR, OperandCount::One, {TokenType::Register})},
    {"LDSTR", Mnemonic(Instruction::LDSTR, OperandCount::One, {TokenType::Register})},
    {"ADDIR", Mnemonic(Instruction::ADDIR, OperandCount::One, {TokenType::Register})},
    {"LDFR", Mnemonic(Instruction::LDFR, OperandCount::One, {TokenType::Register})},
    {"LDBR", Mnemonic(Instruction::LDBR, OperandCount::One, {TokenType::Register})},
    {"LDMIR", Mnemonic(Instruction::LDMIR, OperandCount::One, {TokenType::Register})},
    {"LDRMI", Mnemonic(Instruction::LDRMI, OperandCount::One, {TokenType::Register})}
};