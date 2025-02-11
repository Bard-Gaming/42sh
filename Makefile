##
## EPITECH PROJECT, 2024
## Project - minishell_1
## File description:
## Makefile used to help
## and facilitate the compilation
## of minishell_1
##

CC = gcc
CFLAGS =

NAME = mysh

INCLUDE_DIR = include/

SRC_FILES = main.c										\
			src/arguments/argument_buffer_append.c		\
			src/arguments/argument_buffer_create.c		\
			src/arguments/argument_buffer_delete.c		\
			src/arguments/argument_buffer_from_line.c	\
			src/io/sh_puterr.c							\
			src/shell/shell_mainloop.c					\
			src/string/sh_strdup.c						\
			src/string/sh_strlen.c						\
			src/string/sh_strndup.c						\

.PHONY = all debug clean fclean re

all: $(NAME)

$(NAME):
	@$(CC) -o $(NAME) $(CFLAGS) $(SRC_FILES) -I./$(INCLUDE_DIR)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: fclean $(NAME)

sanitize: CFLAGS += -g -Wall -Wextra -Werror -static-libasan -fsanitize=address
sanitize: fclean $(NAME)

clean:

fclean: clean
	@rm -f $(NAME)

re: fclean all
