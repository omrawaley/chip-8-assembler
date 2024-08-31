
# Chip-8 Assembler

A basic assembler with labels that can be used to create programs for the Chip-8.


## Authors

- [@omrawaley](https://www.github.com/omrawaley)


## Instruction Table

| Mnemonic | Opcode     | Operands                |
| :-------- | :------- | :------------------------- |
| `CLS` | `00E0` | None |
| `RET` | `00EE` | None |
| `JMP` | `1NNN` | Addr |
| `CALL` | `2NNN` | Addr |
| `JMPL` | `3NNN`* | Label |
| `SERB` | `3XNN` | Reg, Byte |
| `SNERB` | `4XNN` | Reg, Byte |
| `SERR` | `5XY0` | Reg, Reg |
| `LDRB` | `6XNN` | Reg, Byte |
| `ADDRB` | `7XNN` | Reg, Byte |
| `LDRR` | `8XY0` | Reg, Reg |
| `OR` | `8XY1` | Reg, Reg |
| `AND` | `8XY2` | Reg, Reg |
| `XOR` | `8XY3` | Reg, Reg |
| `ADDRR` | `8XY4` | Reg, Reg |
| `SUBRR` | `8XY5` | Reg, Reg |
| `SHR` | `8XY6` | Reg, Reg |
| `SUBNRR` | `8XY7` | Reg, Reg |
| `SHL` | `8XYE` | Reg, Reg |
| `SNERR` | `9XY0` | Reg, Reg |
| `LDI` | `ANNN` | Addr |
| `JMP0` | `BNNN` | Addr |
| `RND` | `CXNN` | Reg, Byte |
| `DRW` | `DXYN` | Reg, Reg, Nibble |
| `SKP` | `EX9E` | Reg |
| `SKNP` | `EXA1` | Reg |
| `LDRDT` | `FX07` | Reg |
| `LDRK` | `FX0A` | Reg |
| `LDDTR` | `FX15` | Reg |
| `LDSTR` | `FX18` | Reg |
| `ADDIR` | `FX1E` | Reg |
| `LDFR` | `FX29` | Reg |
| `LDBR` | `FX33` | Reg |
| `LDMIR` | `FX55` | Reg |
| `LDRMI` | `FX65` | Reg |

*3NNN is not a real Chip-8 opcode. This gets converted to 1NNN where NNN is the address of a label.
## Features

### Comments

Comments can be used to provide information or notes.

Single-line comments are denoted using a semicolon (`;`). 

Comments can either have their own line or be placed after an existing line, but they cannot be placed after labels.

```
; This is a comment!

LDRB 0 A    ;0x200    And this one, too! 
```

### Labels

Labels can be used to mark sections of code which makes jumping easier.

Labels are denoted using a period (`.`).

When referring to an existing label in a `JMPL` instruction, do not include the period.

```
.add
ADDRR 3 4   ;0x200  Add reg 3 to reg 4

JMPL add    ;0x202  Jump to 0x200
```
## Installation

Compile with `make`.

```bash
g++ chip8asm.cpp -o chip8asm -std=c++17
```
## Usage

```bash
./chip8asm <path-to-asm> <name-of-binary>
```

## Todo

- Remove `3NNN` and either preprocess labels or enable `JMP` to be used for labels as well as 12-bit addresses.
- Add a preprocessor
- Add text replacement (like #define)

## License

Chip-8 Assembler - [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0)

