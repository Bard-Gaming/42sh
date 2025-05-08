##
## EPITECH PROJECT, 2024
## Project - 42parser
## File description:
## Makefile used to help
## and facilitate the
## compilation of the
## 42parser library
##

CC = gcc
CFLAGS =

NAME = libparse.a

INCLUDE_DIRS = -I./include

SRC_FILES =	src/ast/argument/ast_argument_add_char.c					\
			src/ast/argument/ast_argument_add_node.c					\
			src/ast/argument/ast_argument_create.c						\
			src/ast/argument/ast_argument_delete.c						\
			src/ast/argument/ast_argument_grow.c						\
			src/ast/ast_if_stmnt/ast_if_stmnt_add.c						\
			src/ast/ast_if_stmnt/ast_if_stmnt_create.c					\
			src/ast/ast_if_stmnt/ast_if_stmnt_delete.c					\
			src/ast/ast_if_stmnt/ast_if_stmnt_grow.c					\
			src/ast/node_buffer/ast_node_buffer_append.c				\
			src/ast/node_buffer/ast_node_buffer_create.c				\
			src/ast/node_buffer/ast_node_buffer_delete.c				\
			src/ast/print/ast_print_argument.c							\
			src/ast/print/ast_print_binary_operation.c					\
			src/ast/print/ast_print_container.c							\
			src/ast/print/ast_print_indent.c							\
			src/ast/print/ast_print_node.c								\
			src/ast/print/ast_print_raw_argument.c						\
			src/ast/print/ast_print_substitution.c						\
			src/ast/print/ast_print_variable.c							\
			src/ast/ast_create.c										\
			src/ast/ast_delete.c										\
			src/ast/ast_delete_binop_data.c								\
			src/ast/ast_foreach_loop_delete.c							\
			src/ast/ast_print.c											\
			src/ast/ast_redirect_delete.c								\
			src/ast/ast_strtype.c										\
			src/ast/ast_while_loop_delete.c								\
			src/config/parser_config_get.c								\
			src/config/parser_config_set_substitute.c					\
			src/error/parser_critical_error.c							\
			src/error/parser_errno.c									\
			src/error/parser_perror.c									\
			src/lexer/lexer_consume.c									\
			src/lexer/lexer_is_argument_char.c							\
			src/lexer/lexer_is_redirect_in.c							\
			src/lexer/lexer_is_redirect_out.c							\
			src/lexer/lexer_is_whitespace.c								\
			src/lexer/lexer_load_src.c									\
			src/lexer/lexer_make_argument.c								\
			src/lexer/lexer_make_argument_str.c							\
			src/lexer/lexer_make_error.c								\
			src/lexer/lexer_make_generic.c								\
			src/lexer/lexer_make_operator.c								\
			src/lexer/lexer_make_raw_argument.c							\
			src/lexer/lexer_make_redirect_in.c							\
			src/lexer/lexer_make_redirect_out.c							\
			src/lexer/lexer_scan.c										\
			src/parser/grammar/parse_atom.c								\
			src/parser/grammar/parse_expression.c						\
			src/parser/grammar/parse_statement.c						\
			src/parser/grammar/parse_subatom.c							\
			src/parser/implementation/parse_argument.c					\
			src/parser/implementation/parse_binary_operation.c			\
			src/parser/implementation/parse_command.c					\
			src/parser/implementation/parse_compound.c					\
			src/parser/implementation/parse_condition.c					\
			src/parser/implementation/parse_foreach_loop.c				\
			src/parser/implementation/parse_if_statement.c				\
			src/parser/implementation/parse_pipeline.c					\
			src/parser/implementation/parse_program.c					\
			src/parser/implementation/parse_raw_argument.c				\
			src/parser/implementation/parse_redirect_append.c			\
			src/parser/implementation/parse_redirect_in.c				\
			src/parser/implementation/parse_redirect_non_fd.c			\
			src/parser/implementation/parse_redirect_out.c				\
			src/parser/implementation/parse_while_loop.c				\
			src/parser/parse_input.c									\
			src/parser/parse_input_dynamic.c							\
			src/parser/parser_init.c									\
			src/parser/parser_next.c									\
			src/parser/parser_scan.c									\
			src/parser/parser_scan_keyword.c							\
			src/parser/parser_term.c									\
			src/preparser/preparse.c									\
			src/preparser/preparser_add_char.c							\
			src/preparser/preparser_add_str.c							\
			src/preparser/preparser_add_token.c							\
			src/preparser/preparser_grow.c								\
			src/preparser/preparser_init.c								\
			src/preparser/preparser_next.c								\
			src/preparser/preparser_term.c								\
			src/token/token_create.c									\
			src/token/token_delete.c									\
			src/token/token_match.c										\
			src/token/token_value.c										\

OBJ_FILES = $(SRC_FILES:.c=.o)

TEST_NAME = unit_tests

TEST_SRC =	tests/syntax/test_basic.c									\
			tests/syntax/test_commands.c								\
			tests/syntax/test_compounds.c								\
			tests/syntax/test_conditionals.c							\
			tests/syntax/test_foreach_loops.c							\
			tests/syntax/test_operations.c								\
			tests/syntax/test_pipes.c									\
			tests/syntax/test_redirections.c							\
			tests/syntax/test_substitutions.c							\
			tests/syntax/test_variables.c								\
			tests/syntax/test_while_loops.c								\

.PHONY = all debug sanitize tests_run clean fclean re _no_repo

all: $(NAME)

%.o: %.c
	@$(CC) -c $< $(INCLUDE_DIRS) $(CFLAGS) -o $@

$(NAME): $(OBJ_FILES)
	@ar rc $(NAME) $(OBJ_FILES)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: fclean $(NAME)

sanitize: CFLAGS += -g -fsanitize=address
sanitize: fclean $(NAME)

tests_run: fclean $(NAME)
tests_run: CFLAGS += -L. -lparse --coverage -lcriterion
tests_run:
	@$(CC) -o $(TEST_NAME) $(TEST_SRC) $(INCLUDE_DIRS) $(CFLAGS)
	@./$(TEST_NAME)

clean:
	@rm -f $(SRC_FILES:.c=.gcda)
	@rm -f $(SRC_FILES:.c=.gcno)
	@rm -f *.gcda
	@rm -f *.gcno
	@rm -f $(TEST_NAME)
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all

_no_repo:
	@rm -f README.md
	@rm -f LICENSE
	@rm -rf .git
	@rm -rf tests
