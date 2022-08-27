all: test

CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g3 -fsanitize=address
LDFLAGS = -fsanitize=address

.PHONY: test
test: main.exe
	find cases -name "*.txt" | sort | xargs -L1 sh test.sh

.PHONY:
clean:
	rm *.o

.PHONY: fclean
fclean: clean
	rm main.exe

.PHONY: re
re: fclean
	$(MAKE) all

main.exe: main.o ../../get_next_line.a
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: ../../get_next_line.a
../../get_next_line.a:
	$(MAKE) -C ../.. SANITIZE=address BUFFER_SIZE=4
