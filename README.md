# Regular Expression to Finite Automata Converter

## About

Given a postfix Regular Expression, this system generates the transitions for a Finite Automata which accepts said postfix Regular Expression.

## Versioning

**VERSION:** 1.0

**RELEASE:** N/A

**LAST UPDATED:** October 8th, 2018

## Resources

**makeNFA.c:** Implementation of main functionality.

**stack.c:** Implementation of a stack for use in **makeNFA.c**

**stack.h:** Header file for **stack.c** containing definitions, structures, and prototypes for the implementation.

**Makefile:** Makefile for building the system.

**test.txt:** Document containing postfix expressions for testing.

## How To Use

To use the system:
1. Run `make` to compile the system.
2. Run `make run < FILEPATH` to run the system. Make sure FILEPATH specifies the path to a file containing legal postfix Regular Expressions. Using the included file **test.txt** this would be `make run < test.txt`.
3. Run `make clean` to clean up the directory, removing all executables and object files.

## Future Development

No future development is planned at this time.
