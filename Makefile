build:
	gcc -g -Wall -Wextra main.c utils.c hashtable_utils.c books_utils.c definitions_utils.c -o main

run:
	./main

clean:
	rm -rf main