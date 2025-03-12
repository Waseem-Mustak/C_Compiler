#EMU 8086 MicroC Translator

An educational tool that converts a subset of C language into 8086-compatible assembly code for emulation environments.

## Overview

This lightweight translator takes C source code and produces assembly instructions that can be executed in an 8086 emulator. Designed for educational purposes to demonstrate compiler construction concepts.

## Build Requirements

- Ubuntu/Linux environment
- Development tools:
  ```bash
  sudo apt install flex bison build-essential
  ```

## Quick Usage Guide

```bash
git clone https://github.com/Waseem-Mustak/8086-microc
cd 8086-microc
bash run.sh
```

The translator will generate `emu8086.txt` with 8086-compatible instructions.

## Technical Components

### Lexical Analyzer
Built with Flex for efficient token recognition of C syntax elements.

### Parser & Semantic Handler
Utilizes Bison grammar definitions to validate syntax and perform semantic checks.

### Symbol Management
Custom implementation handles variable declarations, scoping rules, and type checking.


## Language Support

### Control Structures
- Conditional statements (if-else)
- Iteration constructs (while, for)

### Function Capabilities
- Declaration with parameters
- Return value handling
- Recursion support

### Data Types
- Integer values
- Floating-point numbers
- Character data
- String constants

### Operations
- Arithmetic calculations
- Comparison expressions
- Logical operations

## Development

This project was created as a practical application of compiler theory principles, demonstrating the translation process from high-level language to assembly code.

## Running Generated Code

The assembly output is compatible with standard 8086 emulators like EMU8086. Load the generated `.txt` file to see your C code in action.