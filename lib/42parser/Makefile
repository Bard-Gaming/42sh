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

INCLUDE_DIR = include/

SRC_FILES =	src/ast/ast_command_append.c					\
			src/ast/ast_command_create.c					\
			src/ast/ast_command_delete.c					\
			src/ast/ast_create.c							\
			src/ast/ast_delete.c							\
			src/ast/ast_delete_binop_data.c					\
			src/ast/ast_print.c								\
			src/lexer/lexer_consume.c						\
			src/lexer/lexer_get.c							\
			src/lexer/lexer_is_argument.c					\
			src/lexer/lexer_is_whitespace.c					\
			src/lexer/lexer_load_src.c						\
			src/lexer/lexer_make_argument.c					\
			src/lexer/lexer_make_generic.c					\
			src/lexer/lexer_make_operator.c					\
			src/lexer/lexer_make_string.c					\
			src/lexer/lexer_scan.c							\
			src/parser/parse_atom.c							\
			src/parser/parse_command.c						\
			src/parser/parse_line.c							\
			src/parser/parse_binary_operation.c				\
			src/parser/parse_parenthesis.c					\
			src/parser/parse_statement.c					\
			src/parser/parser_init.c						\
			src/parser/parser_next.c						\
			src/parser/parser_term.c						\
			src/token/token_create.c						\
			src/token/token_delete.c						\
			src/token/token_value.c							\

OBJ_FILES = $(SRC_FILES:.c=.o)

.PHONY = all debug clean fclean re

all: $(NAME)

%.o: %.c
	@$(CC) -c $< -I./$(INCLUDE_DIR) $(CFLAGS) -o $@

$(NAME): $(OBJ_FILES)
	@ar rc $(NAME) $(OBJ_FILES)

debug: CFLAGS += -ggdb -Wall -Wextra
debug: fclean $(NAME)

sanitize: CFLAGS += -g -fsanitize=address
sanitize: fclean $(NAME)

clean:
	@rm -f $(OBJ_FILES)

fclean: clean
	@rm -f $(NAME)

re: fclean all
