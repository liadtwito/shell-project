CC = gcc
FLAGS = -Wall -g

main: main.c
	$(CC) $(FLAGS) -o myShell main.c myFunctions.c

leak:
	valgrind --leak-check=full ./myShell
	
connection:
	./myShell

clean:
	rm -f *.o *.out myShell