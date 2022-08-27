#!/bin/sh

set -e

make SANITIZER=address BUFFER_SIZE=1024 && \
clang \
	-Wall -Wextra -Werror \
	-fsanitize=address -g3 \
	main.c get_next_line.a \
	-o main.exe
