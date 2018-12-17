/* Shawn Hillstrom -- CS 317 -- Project 1 Main Implementation
 * ----------------------------------------------------------
 * Contains main function and helper functions to implement Project 1
 */

#include <stdio.h>
#include <string.h>

#include "stack.h"

#define MAX_BUF_SIZE 100

/* function: createNFA
 * -------------------
 * Create a new NFA.
 *
 * myNFA: Address for new NFA.
 * start: Integer representing start state.
 * final: Integer representing final state.
 */
void createNFA(nfa * myNFA, int start, int final) {
	myNFA->startState = start;
	myNFA->finalState = final;
	myNFA->totTran = 0;
}

/* function: addStateTran
 * ----------------------
 * Add a new state transition to an NFA
 *
 * myNFA: Address for NFA to add new stateTran to.
 * current: Integer representing current state in new stateTran.
 * next: Integer representing next state in new stateTran.
 * symbol: Character representing the transition symbol between current and next.
 */
void addStateTran(nfa * myNFA, int current, int next, char sym) {
	if (myNFA->totTran >= MAX_LIST_SIZE) {
		return;
	}
	myNFA->tranList[myNFA->totTran].currentState = current;
	myNFA->tranList[myNFA->totTran].nextState = next;
	myNFA->tranList[myNFA->totTran].symbol = sym;
	myNFA->tranList[myNFA->totTran].myList = myNFA->tranList;
	myNFA->totTran++;
}

/* function: copyTranList
 * ----------------------
 * Copies the transition list from one NFA to another starting at the end of the new
 * 	NFA's transition list.
 *
 * oldNFA: NFA to copy transition list from.
 * newNFA: NFA to copy transition list to.
 * stateOffset: Integer offset to determine new state number.
 */
void copyTranList(nfa * oldNFA, nfa * newNFA, int stateOffset) {
	int indexOffset = newNFA->totTran;
	for (int i = indexOffset; i < indexOffset + oldNFA->totTran; i++) {
		newNFA->tranList[i].currentState = oldNFA->tranList[i - indexOffset].currentState + stateOffset;
		newNFA->tranList[i].nextState = oldNFA->tranList[i - indexOffset].nextState + stateOffset;
		newNFA->tranList[i].symbol = oldNFA->tranList[i - indexOffset].symbol;
		newNFA->tranList[i].myList = newNFA->tranList;
		newNFA->totTran++;
	}
}

/* function: concatNFA
 * ----------------
 * Performs the concatenation of two NFAs.
 *
 * nfa1: Address of first NFA.
 * nfa2: Address of second NFA.
 * newNFA: Address of new NFA.
 */
void concatNFA(nfa * nfa1, nfa * nfa2, nfa * newNFA) {
	createNFA(newNFA, nfa2->startState, nfa2->finalState + nfa1->finalState);
	copyTranList(nfa2, newNFA, 0);
	addStateTran(newNFA, nfa2->finalState, nfa2->finalState + 1, 'E');
	copyTranList(nfa1, newNFA, nfa2->finalState);
}

/* function: unionNFA
 * ------------------
 * Performs the union of two NFAs.
 *
 * nfa1: Address of first NFA.
 * nfa2: Address of second NFA.
 * newNFA: Address of new NFA.
 */
void unionNFA(nfa * nfa1, nfa * nfa2, nfa * newNFA) {
	createNFA(newNFA, nfa2->startState, nfa2->finalState + nfa1->finalState + 2);
	addStateTran(newNFA, nfa2->startState, nfa2->startState + 1, 'E');
	addStateTran(newNFA, nfa2->startState, nfa1->startState + nfa2->finalState + 1, 'E');
	copyTranList(nfa2, newNFA, 1);
	addStateTran(newNFA, nfa2->finalState + 1, nfa2->finalState + nfa1->finalState + 2, 'E');
	copyTranList(nfa1, newNFA, nfa1->startState + nfa2->finalState);
	addStateTran(newNFA, nfa2->finalState + nfa1->finalState + 1, nfa2->finalState + nfa1->finalState + 2, 'E');
}

/* function: kleeneNFA
 * -------------------
 * Performs the Kleene Star operation on an NFA
 *
 * oldNFA: Address of old NFA.
 * newNFA: Address of new NFA.
 */
void kleeneNFA(nfa * oldNFA, nfa * newNFA) {
	createNFA(newNFA, oldNFA->startState, oldNFA->finalState);
	addStateTran(newNFA, oldNFA->startState, oldNFA->finalState, 'E');
	copyTranList(oldNFA, newNFA, 0);
	addStateTran(newNFA, oldNFA->finalState, oldNFA->startState, 'E');
}

/* function: printNFA
 * ------------------
 * Prints out the state transitions contained in an NFA.
 *
 * myNFA: Address of NFA.
 */
void printNFA(nfa * myNFA) {
	for (int i = 0; i < myNFA->totTran; i++) {
		int current = myNFA->tranList[i].currentState;
		int next = myNFA->tranList[i].nextState;
		char sym = myNFA->tranList[i].symbol;
		if (current == myNFA->startState) {
			printf("(Sq%d, %c) -> ", current, sym);
		} else if (current == myNFA->finalState) {
			printf("(Fq%d, %c) -> ", current, sym);
		} else {
			printf("(q%d, %c) -> ", current, sym);
		}
		if (next == myNFA->startState) {
			printf("Sq%d\n", next);
		} else if (next == myNFA->finalState) {
			printf("Fq%d\n", next);
		} else {
			printf("q%d\n", next);
		}
	}
}

int main() {

	/* Variable Initialization */
	nfa stack[MAX_STACK_SIZE];
	int curIndex = 0;

	char buffer[MAX_BUF_SIZE]; // String buffer.

	while (fgets(buffer, MAX_BUF_SIZE, stdin)) {
		for (int i = 0; i < strlen(buffer); i++) {
			char currentChar = buffer[i];
			if (currentChar == '&') {
				nfa nfa1 = pop(stack, &curIndex);
				nfa nfa2 = pop(stack, &curIndex);
				nfa newNFA;
				concatNFA(&nfa1, &nfa2, &newNFA);
				push(newNFA, stack, &curIndex);
			} else if (currentChar == '|') {
				nfa nfa1 = pop(stack, &curIndex);
				nfa nfa2 = pop(stack, &curIndex);
				nfa newNFA;
				unionNFA(&nfa1, &nfa2, &newNFA);
				push(newNFA, stack, &curIndex);
			} else if (currentChar == '*') {
				nfa oldNFA = pop(stack, &curIndex);
				nfa newNFA;
				kleeneNFA(&oldNFA, &newNFA);
				push(newNFA, stack, &curIndex);
			} else if (currentChar == 'a' || 
				currentChar == 'b' || 
				currentChar == 'c' || 
				currentChar == 'd' || 
				currentChar == 'e' || 
				currentChar == 'E') {
				nfa newNFA;
				createNFA(&newNFA, 1, 2);
				addStateTran(&newNFA, 1, 2, currentChar);
				push(newNFA, stack, &curIndex);
			} else {
				break;
			}
		}
		nfa finalNFA = pop(stack, &curIndex);
		printNFA(&finalNFA);
	}

	return 0;

}
