##
## EPITECH PROJECT, 2024
## Project - readline
## File description:
## Makefile used to help
## and facilitate the compilation
## of the readline library
##

CC = gcc
CFLAGS =

NAME = libreadline.a

INCLUDE_DIRS = -I./include

SRC_FILES =	src/readline.c								\
			src/readline_free.c							\
			src/buffer/rl_buffer_get.c					\
			src/buffer/rl_buffer_add_char.c				\
			src/buffer/rl_buffer_empty.c				\

OBJ_FILES = $(SRC_FILES:%.c=%.o)

.PHONY = all debug sanitize clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) -c $< $(INCLUDE_DIRS) $(CFLAGS) -o $@

$(NAME): $(OBJ_FILES)
	@ar rc $(NAME) $(OBJ_FILES)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: fclean $(NAME)

sanitize: CFLAGS += -g -static-libasan -fsanitize=address
sanitize: fclean $(NAME)

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all
