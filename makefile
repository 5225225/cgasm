CC=clang
CFLAGS=-Wall -Wextra -Werror -pedantic -o cgasm

all:
	@$(CC) $(CFLAGS) exec.c
