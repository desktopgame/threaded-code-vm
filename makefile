PROGRAM = a.out
OBJS = main.o stack.o

$(PROGRAM): $(OBJS)
	$(CC) -g -o $(PROGRAM) $^

main.o: main.c
stack.o: stack.c