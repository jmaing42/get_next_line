#!/bin/sh

set -e

# make SANITIZER=address && \
clang \
	-Wall -Wextra -Werror \
	-fsanitize=address -g3 \
	main.c get_next_line.a \
	-o main.exe
