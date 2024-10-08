
# Chip-8 Assembler

A basic assembler with labels that can be used to create programs for the Chip-8.


## Authors

- [@omrawaley](https://www.github.com/omrawaley)


## Instruction Table

| Mnemonic | Opcode     | Operands                |
| :-------- | :------- | :------------------------- |
| `CLS` | `00E0` | None |
| `RET` | `00EE` | None |
| `JMP` | `1NNN` | Addr OR Label |
| `CALL` | `2NNN` | Addr |
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

When referring to an existing label in a `JMP` instruction, do not include the period.

```
.add
ADDRR 3 4   ;0x200  Add reg 3 to reg 4

JMP add     ;0x202  Jump to 0x200
```

### Definitions

Definitions can be used to assign a name to a value which the preprocessor then replaces with the actual value.

Definitions are denoted using a hashtag (`#`).

If you have ever used C or C++, definitions are essentially `#define`.

```
#count A      ;      Create a definition named "count" with a value of A

.start
SERB 3 count  ;0x200 Skip the next instruction if reg 3's value is A

LDRB 3 count  ;0x202 Load reg 3 with A

JMP start     ;0x204 Jump to 0x200
```

You can also use four arithmetic operators (`+`, `-`, `*`, `/`) with your definitions.

Currently, you can only use one operator per definition, but that is subject to change in the near future.

```
#a 4          ;      Create a definition named "a" with a value of 4
#b 2          ;      Create a definition named "b" with a value of 2

#sum a + b    ;      Create a definition named "sum" with a value of 6
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

## Examples

See the [examples](https://github.com/omrawaley/chip-8-assembler/tree/main/examples) folder for demos and sample programs.

## Todo

- ~~Remove `3NNN` and either preprocess labels or enable `JMP` to be used for labels as well as 12-bit addresses.~~
- ~~Add a preprocessor~~
- ~~Add text replacement (like #define)~~
- Refine the file structure to simplify `main.cpp`
- Add better error handling (e.g. "multiple definitions of label," "definition does not exist")
- ~~Allow arithmetic operators to work on definitions~~

## License

Chip-8 Assembler - [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0)

