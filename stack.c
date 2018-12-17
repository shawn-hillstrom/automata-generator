/* Shawn Hillstrom -- CS 317 -- Project 1 Stack Implementation
 * -----------------------------------------------------------
 * Contains required functions to implement a stack.
 * 	Note: Prototypes for functions and descriptions of functionality are contained in stack.h
 */

#include "stack.h"

void push(nfa item, nfa * stack, int * curIndex) {
	if (*curIndex >= MAX_STACK_SIZE) {
		return;
	}
	stack[*curIndex] = item;
	(*curIndex)++;
}

nfa pop(nfa * stack, int * curIndex) {
	if (*curIndex <= 0) {
		nfa empty;
		empty.startState = 0;
		empty.finalState = 0;
		empty.totTran = 0;
		return empty;
	}
	(*curIndex)--;
	nfa temp = stack[*curIndex];
	return temp;
}
