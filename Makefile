##
## EPITECH PROJECT, 2025
## Project - 42sh
## File description:
## Makefile used to help
## and facilitate the compilation
## of the shell
##

CC = gcc
CFLAGS =

NAME = mysh

PARSE_LIB_DIR = lib/42parser
PARSE_LIB_BIN = $(PARSE_LIB_DIR)/libparse.a

READ_LIB_DIR = lib/42readline
READ_LIB_BIN = $(READ_LIB_DIR)/libreadline.a

INCLUDE_DIRS =	-I./include						\
				-I./$(PARSE_LIB_DIR)/include	\
				-I./$(READ_LIB_DIR)/include		\

LIBS = -L./$(PARSE_LIB_DIR) -lparse -L./$(READ_LIB_DIR) -lreadline

SRC_FILES = main.c														\
			src/builtins/builtin_cd.c									\
			src/builtins/builtin_env.c									\
			src/builtins/builtin_exit.c									\
			src/builtins/builtin_get.c									\
			src/builtins/builtin_setenv.c								\
			src/builtins/builtin_unsetenv.c								\
			src/data/sh_data_create.c									\
			src/data/sh_data_delete.c									\
			src/data/sh_data_from_unix_env.c							\
			src/env/sh_env_create.c										\
			src/env/sh_env_delete.c										\
			src/env/sh_env_delete_unix.c								\
			src/env/sh_env_from_unix.c									\
			src/env/sh_env_get.c										\
			src/env/sh_env_put.c										\
			src/env/sh_env_set.c										\
			src/env/sh_env_to_unix.c									\
			src/env/sh_env_unset.c										\
			src/io/sh_dputs.c											\
			src/io/sh_puterr.c											\
			src/io/sh_putstr.c											\
			src/io/sh_perror.c											\
			src/io/sh_cmd_perror.c										\
			src/shell/interpreter/shell_interpret.c						\
			src/shell/interpreter/shell_interpret_command.c				\
			src/shell/interpreter/shell_interpret_operation_and.c		\
			src/shell/interpreter/shell_interpret_operation_or.c		\
			src/shell/interpreter/shell_interpret_operation_pipe.c		\
			src/shell/interpreter/shell_interpret_program.c				\
			src/shell/shell_exec_command.c								\
			src/shell/shell_get_command_abs_path.c						\
			src/shell/shell_mainloop.c									\
			src/shell/shell_query_input.c								\
			src/shell/shell_subprocess.c								\
			src/string/sh_strchr.c										\
			src/string/sh_strcmp.c										\
			src/string/sh_strcpy.c										\
			src/string/sh_strdup.c										\
			src/string/sh_strjoin.c										\
			src/string/sh_strlen.c										\
			src/string/sh_strncmp.c										\
			src/string/sh_strndup.c										\

OBJ_FILES = $(SRC_FILES:.c=.o)

SUCCESS_MSG_FORMAT = "\033[92;1m   %s\033[0m\n"
ERROR_MSG_FORMAT = "\033[31;1m   %s\033[0m\n"

MAKE_RULE =

.PHONY = all release debug sanitize clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) -c $< $(INCLUDE_DIRS) $(LIBS) $(CFLAGS) -o $@ || \
	(printf $(ERROR_MSG_FORMAT) "Error compiling $<"; false)
	@printf $(SUCCESS_MSG_FORMAT) "Successfully compiled $<"

$(PARSE_LIB_BIN):
	@make -s -C $(PARSE_LIB_DIR) $(MAKE_RULE)

$(READ_LIB_BIN):
	@make -s -C $(READ_LIB_DIR) $(MAKE_RULE)

$(NAME): $(PARSE_LIB_BIN) $(READ_LIB_BIN) $(OBJ_FILES)
	@$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(OBJ_FILES) $(LIBS) -o $(NAME) || \
	(printf $(ERROR_MSG_FORMAT) "Error compiling $@"; false)
	@printf $(SUCCESS_MSG_FORMAT) "Successfully compiled $@"

release: CFLAGS += -Ofast
release: fclean $(NAME)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: MAKE_RULE = debug
debug: fclean $(NAME)


sanitize: CFLAGS += -g -Wall -Wextra -Werror -static-libasan -fsanitize=address
sanitize: MAKE_RULE = sanitize
sanitize: fclean $(NAME)

clean:
	@make -s -C $(PARSE_LIB_DIR) clean
	@make -s -C $(READ_LIB_DIR) clean
	@rm -f $(OBJ_FILES)

fclean: clean
	@make -s -C $(PARSE_LIB_DIR) fclean
	@make -s -C $(READ_LIB_DIR) fclean
	@rm -f $(NAME)

re: fclean all
