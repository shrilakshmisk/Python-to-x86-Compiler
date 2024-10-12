# Python Compiler for x86 Assembly

This project develops a Python compiler that generates x86 assembly code, as a part of CS335 - Compiler Design course offered in 2023-24 even semester at IITK. 

## Features

- **Lexical Analysis**: Uses Flex to convert Python code into a series of tokens, facilitating the parsing process.
- **Syntax Parsing**: Utilizes Bison to construct a syntax tree from the tokens, enabling accurate code interpretation.
- **Hierarchical Symbol Table**: Manages scopes and declarations efficiently, essential for supporting nested structures and scope-based validations.
- **Three Address Code (3AC) IR**: Transforms Python code into a simplified intermediate representation, easing the generation of assembly code.
- **Semantic Analyzer**: Incorporates type checking and extensive error handling to ensure compliance with Python semantics.
- **Runtime Support**: Handles x86 registers and the runtime stack, maintaining activation records for function calls and supporting features like recursion.
- **Advanced Features**: Includes recursion, object-oriented programming with inheritance, lists, control flows, built-in functions (such as `len` and `range`), and typecasting.
