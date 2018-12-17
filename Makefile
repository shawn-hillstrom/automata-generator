CC = gcc
CCFLAGS = -std=c99 -Wall
EXEC = makeNFA
OBJS = makeNFA.o stack.o

${EXEC}: ${OBJS}
	${CC} ${CCFLAGS} -o ${EXEC} ${OBJS}

makeNFA.o: makeNFA.c
	${CC} ${CCFLAGS} -c makeNFA.c

stack.o: stack.c
	${CC} ${CCFLAGS} -c stack.c

run: ${EXEC}
	./${EXEC}

clean:
	rm -f ${EXEC} ${OBJS}
