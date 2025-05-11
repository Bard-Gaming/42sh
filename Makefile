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
			src/builtins/builtin_alias.c								\
			src/builtins/builtin_cd.c									\
			src/builtins/builtin_echo.c									\
			src/builtins/builtin_endif.c								\
			src/builtins/builtin_env.c									\
			src/builtins/builtin_exec.c									\
			src/builtins/builtin_exit.c									\
			src/builtins/builtin_history.c								\
			src/builtins/builtin_reload.c								\
			src/builtins/builtin_repeat.c								\
			src/builtins/builtin_set.c  								\
			src/builtins/builtin_setenv.c								\
			src/builtins/builtin_unalias.c								\
			src/builtins/builtin_unset.c  								\
			src/builtins/builtin_unsetenv.c								\
			src/builtins/builtin_version.c								\
			src/builtins/builtin_where.c								\
			src/builtins/builtin_which.c								\
			src/builtins/sh_get_builtin.c								\
			src/builtins/sh_is_builtin.c								\
			src/data/sh_data_create.c									\
			src/data/sh_data_delete.c									\
			src/data/sh_data_from_unix_env.c							\
			src/data/sh_data_getvar.c									\
			src/data/sh_data_register.c									\
			src/data/sh_data_setvar.c									\
			src/data/sh_data_setenv.c									\
			src/data/sh_env_create.c									\
			src/data/sh_env_delete.c									\
			src/io/sh_cmd_perror.c										\
			src/io/sh_create_temp_file.c								\
			src/io/sh_dputs.c											\
			src/io/sh_perror.c											\
			src/io/sh_print_columns.c									\
			src/memory/sh_memory_failure.c								\
			src/memory/shcalloc.c										\
			src/memory/shmalloc.c										\
			src/memory/shrealloc.c										\
			src/memory/shreallocarray.c									\
			src/shell/autocomplete/shell_autocomplete.c					\
			src/shell/autocomplete/shell_autocomplete_alias.c			\
			src/shell/autocomplete/shell_autocomplete_long.c			\
			src/shell/autocomplete/shell_autocomplete_path.c			\
			src/shell/history/shell_history_add.c						\
			src/shell/history/shell_history_count.c						\
			src/shell/history/shell_history_get.c						\
			src/shell/history/shell_history_open.c						\
			src/shell/interpreter/shell_interpret.c						\
			src/shell/interpreter/shell_interpret_argument.c			\
			src/shell/interpreter/shell_interpret_argument_str.c		\
			src/shell/interpreter/shell_interpret_command.c				\
			src/shell/interpreter/shell_interpret_compound.c			\
			src/shell/interpreter/shell_interpret_condition.c			\
			src/shell/interpreter/shell_interpret_foreach_loop.c		\
			src/shell/interpreter/shell_interpret_if_statement.c		\
			src/shell/interpreter/shell_interpret_operation_and.c		\
			src/shell/interpreter/shell_interpret_operation_or.c		\
			src/shell/interpreter/shell_interpret_operation_pipe.c		\
			src/shell/interpreter/shell_interpret_program.c				\
			src/shell/interpreter/shell_interpret_raw_argument.c		\
			src/shell/interpreter/shell_interpret_redirect.c			\
			src/shell/interpreter/shell_interpret_substitution.c		\
			src/shell/interpreter/shell_interpret_value.c				\
			src/shell/interpreter/shell_interpret_variable.c			\
			src/shell/interpreter/shell_interpret_while_loop.c			\
			src/shell/signal/signal_init.c								\
			src/shell/signal/signal_interrupt.c							\
			src/shell/subprocess/shell_setup_pipe.c						\
			src/shell/subprocess/shell_setup_redirections.c				\
			src/shell/subprocess/shell_subprocess.c						\
			src/shell/shell_alias.c										\
			src/shell/shell_exec_command.c								\
			src/shell/shell_get_command_abs_path.c						\
			src/shell/shell_getcwd.c									\
			src/shell/shell_init.c										\
			src/shell/shell_mainloop.c									\
			src/shell/shell_query_input.c								\
			src/shell/shell_run_file.c									\
			src/shell/shell_run_rc.c									\
			src/shell/shell_system.c									\
			src/shell/shell_update_prompt.c								\
			src/string/sh_basename.c									\
			src/string/sh_itoa.c										\
			src/string/sh_strappend.c									\
			src/string/sh_strdup.c										\
			src/string/sh_strglob.c										\
			src/string/sh_strisname.c									\
			src/string/sh_strisnum.c									\
			src/string/sh_strjoin.c										\
			src/string/sh_strjoinvec.c									\
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
			src/vector/sh_vector_glob.c									\
			src/vector/sh_vector_move.c									\
			src/vector/sh_vector_move_unique.c							\
			src/vector/sh_vector_pop.c									\
			src/vector/sh_vector_push_back.c							\
			src/vector/sh_vector_reserve.c								\

OBJ_FILES = $(SRC_FILES:.c=.o)

TST_BIN = unit_tests

TST_FILES =	$(filter-out main.c, $(SRC_FILES))							\
			tests/unit_tests/create_data_tests.c						\
			tests/unit_tests/capture_stdout.c							\
			tests/unit_tests/builtins/tests_alias.c						\
			tests/unit_tests/builtins/tests_unalias.c					\
			tests/unit_tests/builtins/tests_cd.c						\
			tests/unit_tests/builtins/tests_env.c						\
			tests/unit_tests/builtins/tests_exec.c						\
			tests/unit_tests/builtins/tests_exit.c						\
			tests/unit_tests/builtins/tests_repeat.c					\
			tests/unit_tests/builtins/tests_set.c						\
			tests/unit_tests/builtins/tests_unset.c						\
			tests/unit_tests/builtins/tests_setenv.c					\
			tests/unit_tests/builtins/tests_where.c						\
			tests/unit_tests/builtins/tests_which.c						\
			tests/unit_tests/builtins/tests_get_builtin.c				\
			tests/unit_tests/shell/tests_shell_system.c					\
			tests/unit_tests/shell/tests_getcwd.c						\
			tests/unit_tests/shell/tests_update_prompt.c				\
			tests/unit_tests/shell/tests_run_file.c						\
			tests/unit_tests/shell/tests_run_rc.c						\
			tests/unit_tests/shell/tests_exec_command.c					\
			tests/unit_tests/shell/tests_autocomplete.c					\
			tests/unit_tests/shell/interpreter/tests_redirect.c			\
			tests/unit_tests/shell/interpreter/tests_substitution.c		\
			tests/unit_tests/shell/interpreter/tests_foreach_loop.c		\
			tests/unit_tests/shell/interpreter/tests_while_loop.c		\
			tests/unit_tests/string/tests_strisname.c					\
			tests/unit_tests/string/tests_basename.c					\
			tests/unit_tests/string/tests_itoa.c						\
			tests/unit_tests/string/tests_strappend.c					\
			tests/unit_tests/string/tests_strisnum.c					\
			tests/unit_tests/string/tests_strjoin.c						\
			tests/unit_tests/vector/tests_vector_append_range.c			\
			tests/unit_tests/vector/tests_vector_glob.c					\
			tests/unit_tests/vector/tests_vector_move_unique.c			\
			tests/unit_tests/symbols/tests_symbols_print.c				\
			tests/unit_tests/symbols/tests_symbols_unset.c				\

TST_OBJ = $(TST_FILES:.c=.o)
TST_COV = $(TST_FILES:.c=.gcno) $(TST_FILES:.c=.gcda)


SUCCESS_MSG_FORMAT = "\033[92;1m ✅ %s\033[0m\n"
LIB_SUCCESS_MSG_FORMAT = "\033[94;1m ✅ %s\033[0m\n"
ERROR_MSG_FORMAT = "\033[31;1m❌ %s\033[0m\n"


.PHONY: all release debug sanitize tests_run ftests_run clean fclean re

all: CFLAGS += -Ofast
all: $(NAME)

%.o: %.c
	@$(CC) -c $< $(INCLUDE_DIRS) $(LIBS) $(CFLAGS) -o $@ || \
	(printf $(ERROR_MSG_FORMAT) "Error compiling $<"; false)
	@printf $(SUCCESS_MSG_FORMAT) "Successfully compiled $<"

$(PARSE_LIB_BIN):
	@make -s -C $(PARSE_LIB_DIR) $(MAKE_RULE) || \
	(printf $(ERROR_MSG_FORMAT) "Error building library $@"; false)
	@printf $(LIB_SUCCESS_MSG_FORMAT) "Successfully built $@"

$(READ_LIB_BIN):
	@make -s -C $(READ_LIB_DIR) $(MAKE_RULE) || \
	(printf $(ERROR_MSG_FORMAT) "Error building library $@"; false)
	@printf $(LIB_SUCCESS_MSG_FORMAT) "Successfully built $@"

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

$(TST_BIN): LIBS += -lcriterion
$(TST_BIN): CFLAGS += --coverage -ggdb -Wall -Wextra
$(TST_BIN): $(PARSE_LIB_BIN) $(READ_LIB_BIN) $(TST_OBJ)
	@$(CC) -o $(TST_BIN) $(TST_OBJ) $(INCLUDE_DIRS) $(LIBS) $(CFLAGS) || \
	(printf $(ERROR_MSG_FORMAT) "Error compiling $@"; false)
	@printf $(SUCCESS_MSG_FORMAT) "Successfully compiled $@"

tests_run: $(TST_BIN)
	@./$(TST_BIN)

coverage:
	@gcovr . --exclude tests/ --exclude include/

ftests_run: $(NAME)
	@./tests/run_tests.sh

clean:
	@make -s -C $(PARSE_LIB_DIR) clean
	@make -s -C $(READ_LIB_DIR) clean
	@rm -f $(OBJ_FILES)
	@rm -f $(TST_OBJ)
	@rm -f $(TST_COV)

fclean: clean
	@make -s -C $(PARSE_LIB_DIR) fclean
	@make -s -C $(READ_LIB_DIR) fclean
	@rm -f $(NAME)
	@rm -f $(TST_BIN)

re: fclean all
