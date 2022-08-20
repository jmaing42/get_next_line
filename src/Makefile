NAME := get_next_line.a
CC := clang
AR := ar
CFLAGS := -Wall -Wextra -Werror -g3

TMP_DIR := tmp

BUFFER_SIZE ?= 42
CFLAGS += -DBUFFER_SIZE=$(BUFFER_SIZE)
SUFFIX := .$(BUFFER_SIZE)$(if $(SANITIZER),.$(SANITIZER))

NAME_BASIC := basic$(SUFFIX).a
NAME_BONUS := bonus$(SUFFIX).a

SRCS_BASIC := ./get_next_line.c ./get_next_line_utils.c
SRCS_BONUS := $(SRCS_BASIC:.c=_bonus.c)

$(NAME): all
all: $(TMP_DIR)/$(NAME_BASIC)
	cp $< $(NAME)
bonus: $(TMP_DIR)/$(NAME_BONUS)
	cp $< $(NAME)
clean:
	rm -rf $(TMP_DIR)
fclean: clean
	rm -f $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: all bonus clean fclean re $(NAME)

$(TMP_DIR)/%.a:
	@mkdir -p $(@D)
	$(AR) cr $@ $^
$(TMP_DIR)/%$(SUFFIX).o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@ $(if $(SANITIZER),-fsanitize=$(SANITIZER),)

$(TMP_DIR)/$(NAME_BASIC): $(patsubst ./%.c,$(TMP_DIR)/%$(SUFFIX).o,$(SRCS_BASIC))
$(TMP_DIR)/$(NAME_BONUS): $(patsubst ./%.c,$(TMP_DIR)/%$(SUFFIX).o,$(SRCS_BONUS))
