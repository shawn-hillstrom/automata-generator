/* Shawn Hillstrom -- CS 317 -- Project 1 Stack Header File
 * --------------------------------------------------------
 * Contains all relevant inclusions, macros, structures, and prototypes for stack.c
 */

#ifndef STACK_H
#define STACK_H

/* Macros */
#define MAX_STACK_SIZE 100
#define MAX_LIST_SIZE 100

/* typedef: stateTran
 * ------------------
 * State transition structure type-defined as stateTran.
 *
 * currentState: Integer representing the current state.
 * nextState: Integer representing the next state in the transition.
 * symbol: Symbol for transition.
 * nextTran: Next transition in the list of transitions.
 */
typedef struct stateTran stateTran;
struct stateTran {
	int currentState;
	int nextState;
	char symbol;
	stateTran * myList;
};

/* typedef: nfa
 * ------------
 * nfa structure type-defined as nfa.
 *
 * startState: Integer representing the starting state.
 * finalState: Integer representing the final state.
 * transitions: Pointer to a list of transitions.
 */
typedef struct nfa nfa;
struct nfa {
	int startState;
	int finalState;
	int totTran;
	stateTran tranList[MAX_LIST_SIZE];
};

/* function: push
 * --------------
 * Push an item onto the stack.
 *
 * item: Item to push onto the stack.
 * stack: The stack to push item onto.
 * curIndex: Current index on the stack.
 */
void push(nfa item, nfa * stack, int * curIndex);

/* function: pop
 * -------------
 * Pop an item off of the stack.
 *
 * stack: The stack to pop and item off of.
 * curIndex: Current index on the stack.
 *
 * returns: The item popped off of the stack or an empty NFA on failure.
 */
nfa pop(nfa * stack, int * curIndex);

#endif
