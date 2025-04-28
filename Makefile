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

NAME = 42sh

PARSE_LIB_DIR = lib/42parser
PARSE_LIB_BIN = $(PARSE_LIB_DIR)/libparse.a

READ_LIB_DIR = lib/42readline
READ_LIB_BIN = $(READ_LIB_DIR)/libreadline.a

MAKE_RULE =

INCLUDE_DIRS =	-I./include						\
				-I./$(PARSE_LIB_DIR)/include	\
				-I./$(READ_LIB_DIR)/include		\

LIBS = -L./$(PARSE_LIB_DIR) -lparse -L./$(READ_LIB_DIR) -lreadline

SRC_FILES = main.c														\
			src/builtins/builtin_cd.c									\
			src/builtins/builtin_env.c									\
			src/builtins/builtin_exec.c									\
			src/builtins/builtin_exit.c									\
			src/builtins/builtin_reload.c								\
			src/builtins/builtin_repeat.c								\
			src/builtins/builtin_setenv.c								\
			src/builtins/builtin_unsetenv.c								\
			src/builtins/builtin_which.c								\
			src/builtins/builtin_where.c								\
			src/builtins/builtin_set.c  								\
			src/builtins/builtin_unset.c  								\
			src/builtins/sh_get_builtin.c								\
			src/data/sh_data_create.c									\
			src/data/sh_data_delete.c									\
			src/data/sh_data_from_unix_env.c							\
			src/data/sh_data_getvar.c									\
			src/data/sh_data_setvar.c									\
			src/data/sh_data_setenv.c									\
			src/env/sh_env_create.c										\
			src/env/sh_env_delete.c										\
			src/io/sh_cmd_perror.c										\
			src/io/sh_create_temp_file.c								\
			src/io/sh_dputs.c											\
			src/io/sh_perror.c											\
			src/memory/sh_memory_failure.c								\
			src/memory/shcalloc.c										\
			src/memory/shmalloc.c										\
			src/memory/shrealloc.c										\
			src/memory/shreallocarray.c									\
			src/shell/interpreter/shell_interpret.c						\
			src/shell/interpreter/shell_interpret_argument.c			\
			src/shell/interpreter/shell_interpret_command.c				\
			src/shell/interpreter/shell_interpret_compound.c			\
			src/shell/interpreter/shell_interpret_operation_and.c		\
			src/shell/interpreter/shell_interpret_operation_or.c		\
			src/shell/interpreter/shell_interpret_operation_pipe.c		\
			src/shell/interpreter/shell_interpret_program.c				\
			src/shell/interpreter/shell_interpret_raw_argument.c		\
			src/shell/interpreter/shell_interpret_redirect.c			\
			src/shell/signal/signal_init.c								\
			src/shell/signal/signal_interrupt.c							\
			src/shell/subprocess/shell_setup_pipe.c						\
			src/shell/subprocess/shell_setup_redirections.c				\
			src/shell/subprocess/shell_subprocess.c						\
			src/shell/shell_display_prompt.c							\
			src/shell/shell_exec_command.c								\
			src/shell/shell_get_command_abs_path.c						\
			src/shell/shell_getcwd.c									\
			src/shell/shell_mainloop.c									\
			src/shell/shell_query_input.c								\
			src/shell/shell_run_file.c									\
			src/shell/shell_run_rc.c									\
			src/shell/shell_system.c									\
			src/string/sh_basename.c									\
			src/string/sh_itoa.c										\
			src/string/sh_strisname.c									\
			src/string/sh_strisnum.c									\
			src/string/sh_strjoin.c										\
			src/symbols/sh_symbols_create.c								\
			src/symbols/sh_symbols_delete.c								\
			src/symbols/sh_symbols_dup.c								\
			src/symbols/sh_symbols_get.c								\
			src/symbols/sh_symbols_hash.c								\
			src/symbols/sh_symbols_print.c								\
			src/symbols/sh_symbols_set.c								\
			src/symbols/sh_symbols_unset.c								\
			src/vector/sh_vector_append_range.c							\
			src/vector/sh_vector_delete.c								\
			src/vector/sh_vector_push_back.c							\
			src/vector/sh_vector_reserve.c								\

OBJ_FILES = $(SRC_FILES:.c=.o)

TST_BIN = unit_tests

TST_FILES =	$(filter-out main.c, $(SRC_FILES))							\
			tests/unit_tests/builtins/tests_cd.c						\
			tests/unit_tests/builtins/tests_env.c						\


SUCCESS_MSG_FORMAT = "\033[92;1m   %s\033[0m\n"
ERROR_MSG_FORMAT = "\033[31;1m   %s\033[0m\n"


.PHONY: all release debug sanitize tests_run ftests_run clean fclean re

all: CFLAGS += -Ofast
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

debug: CFLAGS += -ggdb -Wall -Wextra
debug: MAKE_RULE = debug
debug: fclean $(NAME)

sanitize: CFLAGS += -g -Wall -Wextra -Werror -lasan -fsanitize=address
sanitize: MAKE_RULE = sanitize
sanitize: fclean $(NAME)

tests_run: LIBS += -lcriterion
tests_run: CFLAGS += --coverage
tests_run: $(PARSE_LIB_BIN) $(READ_LIB_BIN)
	@$(CC) -o $(TST_BIN) $(TST_FILES) $(INCLUDE_DIRS) $(LIBS) $(CFLAGS)
	@./$(TST_BIN) || true
	@gcovr .

ftests_run: $(NAME)
	@./tests/run_tests.sh

clean:
	@make -s -C $(PARSE_LIB_DIR) clean
	@make -s -C $(READ_LIB_DIR) clean
	@rm -f $(OBJ_FILES)
	@rm -f *.gcno
	@rm -f *.gcda

fclean: clean
	@make -s -C $(PARSE_LIB_DIR) fclean
	@make -s -C $(READ_LIB_DIR) fclean
	@rm -f $(NAME)
	@rm -f $(TST_BIN)

re: fclean all
