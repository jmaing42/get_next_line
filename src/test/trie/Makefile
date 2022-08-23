all: test

CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -fsanitize=address
LDFLAGS = -fsanitize=address

.PHONY: test
test: main.exe
	find cases -name "*.txt" | xargs ./main.exe

main.exe: main.o ../../get_next_line.a
	$(CC) $(LDFLAGS) -o $@ $^

re: fclean
	$(MAKE) all
