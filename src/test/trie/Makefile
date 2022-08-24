all: test

CC = clang
CFLAGS = -Wall -Wextra -Werror -pedantic -std=c99 -g3 -fsanitize=address
LDFLAGS = -fsanitize=address

.PHONY: test
test: main.exe
	find cases -name "*.txt" | xargs ./main.exe
clean:
	rm *.o
fclean: clean
	rm main.exe
re: fclean
	$(MAKE) all
main.exe: main.o ../../get_next_line.a
	$(CC) $(LDFLAGS) -o $@ $^
