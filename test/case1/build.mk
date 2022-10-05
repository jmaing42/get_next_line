Q := $(if $(filter 1,$(V) $(VERBOSE)),,@)

CC := clang
CFLAGS := -Wall -Wextra -Werror -std=c99 -pedantic $(if $(SANITIZER),-fsanitize=$(SANITIZER),)
AR := ar
ARFLAGS := cr$(if $(filter 3,$(V) $(VERBOSE)),v,)

ifeq ($(BUFFER_SIZE),)
$(error Bad BUFFER_SIZE)
else
CFLAGS += -DBUFFER_SIZE=$(BUFFER_SIZE)
endif

ifeq ($(PROFILE),release)
CFLAGS += -O3 -DNDEBUG
else ifeq ($(PROFILE),debug)
CFLAGS += -g3 -DDEBUG
else
$(error Bad profile)
endif

SUFFIX := .$(PROFILE)$(if $(SANITIZER),.$(SANITIZER))-$(BUFFER_SIZE)

all: libget_next_line$(SUFFIX).a

get_next_line$(SUFFIX).o get_next_line_utils$(SUFFIX).o: %$(SUFFIX).o: %.c get_next_line.h
	$Q$(CC) $(CFLAGS) -o $@ -c $<

libget_next_line%.a: get_next_line%.o get_next_line_utils%.o
	$Q$(AR) $(ARFLAGS) $@ $^
