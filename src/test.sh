clang \
	-Wall -Wextra -Werror \
	-fsanitize=address -g3 \
	test.c get_next_line_utils_bonus.c \
	-o test.exe \
	&& ./test.exe
