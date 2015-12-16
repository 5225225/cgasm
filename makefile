CC=clang
CFLAGS=-Werror -Weverything -Wno-sign-conversion -o cgasm

all:
	@$(CC) $(CFLAGS) exec.c
