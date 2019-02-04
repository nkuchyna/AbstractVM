# AbstractVM
Simple virtual machine that can interpret programs written in a basic assembly language | UNIT Factory
------------------------------------------------------------------------------------------------------
- AbstractVM is a machine that uses a stack to compute simple arithmetic expressions. These arithmetic expressions are provided to the machine as basic assembly programs.
-  Composed of a series of instructions, with one instruction per line (push, pop, dump, assert, sub, mul, div, mod, print, exit).
- In case of error (lexical, logical or others) AbstractVM raises an exception.
- Machine is able to run programs from a file passed as a parameter and from the standard input.

BONUS PART
- diagnosing all errors in a file/standart_input without stopping at the first error encountered;
- additional instructions (min, max, clear, compare, square);
- lexer/parser couple, with clearly defined roles.

***Usage:*** 
*./avm  <<-- for reading comands from standart input
./avm  [file ] <<-- reading comands from file*
