CC := clang
AR := ar
CFLAGS := -Wall -Wextra -Werror
TMPS := $(OTHER_USEFUL_FILES)

TMP_DIR := tmp

all: $(NAME) $(OTHER_USEFUL_FILES)
bonus: all
clean:
	rm -rf $(OTHER_USEFUL_FILES) tmp
fclean: clean
	rm -f $(NAME)
re:
	$(MAKE) fclean
	$(MAKE) all
.PHONY: all bonus clean fclean re

BUFFER_SIZE ?= 42
CFLAGS += -D

SUFFIX := .$(TARGET).$(PROFILE)$(if $(SANITIZER),.$(SANITIZER))

$(TMP_DIR)/%.a:
	$Qmkdir -p $(@D)
	$Q$(AR) rcs $@ $^
$(TMP_DIR)/%$(SUFFIX).o: %.c
	$Qmkdir -p $(@D)
	$Q$(CC) $(CFLAGS) -c $< -o $@ -MMD $(if $(SANITIZER),-fsanitize=$(SANITIZER),)

$(TMP_DIR)/ft_printf$(SUFFIX).a: $(patsubst ./%.c,$(TMP_DIR)/%$(SUFFIX).o,$(SRCS))
.PHONY: $(NAME)
$(NAME): $(TMP_DIR)/ft_printf$(SUFFIX).a
	$Qcp $< $@

-include $(TMP_DIR)/$(SRCS:.c=$(SUFFIX).d)
