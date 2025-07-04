# Compiler and linker settings
CC = gcc
AR = ar
CFLAGS = -Wall -Wextra -g
CFLAGS_COMP = $(CFLAGS) -Iinclude
CFLAGS_CMD = $(CFLAGS) -Iinclude
LD_FLAGS_COMP =
LD_FLAGS_CMD =

# Sources and objects
SRCS_COMP = $(wildcard src/compiler/*.c src/compiler/*/*.c) $(wildcard src/utils/*.c src/utils/*/*.c)
OBJS_COMP = $(SRCS_COMP:.c=.o)

SRCS_CMD = $(wildcard src/cmd/*.c src/cmd/*/*.c) $(wildcard src/utils/*.c src/utils/*/*.c)
OBJS_CMD = $(SRCS_CMD:.c=.o)

# Output names
NAME = cdy
COMP_LIB = libcdy.a

# Build targets
all: $(NAME)

$(NAME): $(OBJS_CMD) $(COMP_LIB)
	$(CC) $(OBJS_CMD) $(COMP_LIB) -o $(NAME) $(LD_FLAGS_CMD)

$(COMP_LIB): $(OBJS_COMP)
	$(AR) -rcs $@ $^

# Compilation rules
src/cmd/%.o: src/cmd/%.c
	$(CC) -o $@ -c $< $(CFLAGS_CMD)

src/compiler/%.o: src/compiler/%.c
	$(CC) -o $@ -c $< $(CFLAGS_COMP)

# Cleaning rules
clean:
	rm -f $(OBJS_COMP) $(OBJS_CMD) $(COMP_LIB) $(NAME)

re: clean all

.PHONY: all clean
