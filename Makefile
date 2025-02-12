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
			src/builtins/builtin_cd.c					\
			src/builtins/builtin_env.c					\
			src/builtins/builtin_exit.c					\
			src/builtins/builtin_get.c					\
			src/builtins/builtin_setenv.c				\
			src/builtins/builtin_unsetenv.c				\
			src/env/sh_env_create.c						\
			src/env/sh_env_delete.c						\
			src/env/sh_env_delete_unix.c				\
			src/env/sh_env_from_unix.c					\
			src/env/sh_env_get.c						\
			src/env/sh_env_put.c						\
			src/env/sh_env_set.c						\
			src/env/sh_env_to_unix.c					\
			src/env/sh_env_unset.c						\
			src/io/sh_dputs.c							\
			src/io/sh_puterr.c							\
			src/io/sh_putstr.c							\
			src/shell/shell_execline.c					\
			src/shell/shell_mainloop.c					\
			src/shell/shell_parse_program.c				\
			src/shell/shell_query_command.c				\
			src/shell/shell_subprocess.c				\
			src/string/sh_strcmp.c						\
			src/string/sh_strcpy.c						\
			src/string/sh_strdup.c						\
			src/string/sh_strjoin.c						\
			src/string/sh_strlen.c						\
			src/string/sh_strncmp.c						\
			src/string/sh_strndup.c						\

.PHONY = all debug clean fclean re

all: $(NAME)

$(NAME):
	@$(CC) -o $(NAME) $(CFLAGS) $(SRC_FILES) -I./$(INCLUDE_DIR)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: fclean $(NAME)

sanitize: CFLAGS += -g -Wall -Wextra -Werror -static-libasan -fsanitize=address
sanitize: fclean $(NAME)

my_segfault:
	@test ! -f tmp.c && (echo "main;" > tmp.c && \
	$(CC) -o my_segfault tmp.c 2>/dev/null; rm tmp.c)

clean:

fclean: clean
	@rm -f my_segfault
	@rm -f $(NAME)

re: fclean all
