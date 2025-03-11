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


SRC_FILES = main.c										\
			src/arguments/argument_buffer_append.c		\
			src/arguments/argument_buffer_create.c		\
			src/arguments/argument_buffer_delete.c		\
			src/arguments/argument_buffer_from_line.c	\
			src/arguments/arguments_is_valid_line.c		\
			src/arguments/arguments_parse_arg.c			\
			src/builtins/builtin_cd.c					\
			src/builtins/builtin_env.c					\
			src/builtins/builtin_exit.c					\
			src/builtins/builtin_get.c					\
			src/builtins/builtin_setenv.c				\
			src/builtins/builtin_unsetenv.c				\
			src/data/sh_data_create.c					\
			src/data/sh_data_delete.c					\
			src/data/sh_data_from_unix_env.c			\
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
			src/io/sh_perror.c							\
			src/io/sh_cmd_perror.c						\
			src/shell/shell_exec_command.c				\
			src/shell/shell_get_command_abs_path.c		\
			src/shell/shell_interpret_input.c			\
			src/shell/shell_mainloop.c					\
			src/shell/shell_query_input.c				\
			src/shell/shell_subprocess.c				\
			src/string/sh_str_contains_char.c			\
			src/string/sh_strcmp.c						\
			src/string/sh_strcpy.c						\
			src/string/sh_strdup.c						\
			src/string/sh_strjoin.c						\
			src/string/sh_strlen.c						\
			src/string/sh_strncmp.c						\
			src/string/sh_strndup.c						\


PARSE_LIB_DIR = lib/42parser
PARSE_LIB_BIN = $(PARSE_LIB_DIR)/libparse.a

INCLUDE_DIRS = -I./include/ -I./$(PARSE_LIB_DIR)/include
LIBS = -L./$(PARSE_LIB_DIR) -lparse

.PHONY = all release debug clean fclean re

all: $(NAME)

$(PARSE_LIB_BIN):
	@make -s -C $(PARSE_LIB_DIR)

$(NAME): $(PARSE_LIB_BIN)
	@$(CC) -o $(NAME) $(CFLAGS) $(SRC_FILES) $(INCLUDE_DIRS) $(LIBS)

release: CFLAGS += -Ofast
release: fclean $(NAME)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: fclean $(NAME)

sanitize: CFLAGS += -g -Wall -Wextra -Werror -static-libasan -fsanitize=address
sanitize: fclean $(NAME)

my_segfault:
	@test ! -f tmp.c && (echo "main;" > tmp.c && \
	$(CC) -o my_segfault tmp.c 2>/dev/null; rm tmp.c)

clean:
	@make -s -C $(PARSE_LIB_DIR) clean

fclean: clean
	@make -s -C $(PARSE_LIB_DIR) fclean
	@rm -f my_segfault
	@rm -f $(NAME)

re: fclean all
