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

SRC_FILES =	src/ast/ast_create.c										\
			src/ast/ast_delete.c										\
			src/ast/ast_delete_binop_data.c								\
			src/ast/ast_node_buffer_append.c							\
			src/ast/ast_node_buffer_create.c							\
			src/ast/ast_node_buffer_delete.c							\
			src/ast/ast_print.c											\
			src/ast/ast_redirect_delete.c								\
			src/ast/ast_strtype.c										\
			src/error/parser_errno.c									\
			src/error/parser_perror.c									\
			src/lexer/lexer_consume.c									\
			src/lexer/lexer_is_argument_char.c							\
			src/lexer/lexer_is_redirect_in.c							\
			src/lexer/lexer_is_redirect_out.c							\
			src/lexer/lexer_is_whitespace.c								\
			src/lexer/lexer_load_src.c									\
			src/lexer/lexer_make_argument.c								\
			src/lexer/lexer_make_error.c								\
			src/lexer/lexer_make_format_string.c						\
			src/lexer/lexer_make_generic.c								\
			src/lexer/lexer_make_operator.c								\
			src/lexer/lexer_make_raw_string.c							\
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
			src/parser/implementation/parse_parenthesis.c				\
			src/parser/implementation/parse_pipeline.c					\
			src/parser/implementation/parse_program.c					\
			src/parser/implementation/parse_redirect_append.c			\
			src/parser/implementation/parse_redirect_in.c				\
			src/parser/implementation/parse_redirect_non_fd.c			\
			src/parser/implementation/parse_redirect_out.c				\
			src/parser/parse_input.c									\
			src/parser/parser_init.c									\
			src/parser/parser_next.c									\
			src/parser/parser_term.c									\
			src/token/token_create.c									\
			src/token/token_delete.c									\
			src/token/token_value.c										\

OBJ_FILES = $(SRC_FILES:.c=.o)

TEST_NAME = unit_tests

TEST_SRC =	tests/syntax/test_commands.c								\
			tests/syntax/test_compounds.c								\
			tests/syntax/test_pipes.c									\
			tests/syntax/test_redirections.c							\

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
