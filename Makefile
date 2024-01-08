CC=g++
FLAGS= -Wall -Werror -Wextra
MEM= -fsanitize


rebuild: clean all

all:
	clear
	$(CC) $(FLAGS) -o main.exe checkers.cpp main.cpp
	./main.exe
clean:
	rm -rf main.exe
