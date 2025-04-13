/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Main header file for
** everything related to
** parsing
*/

#ifndef PARSER_PARSE_H
    #define PARSER_PARSE_H
    #include <42parser/ast.h>
    #include <42parser/token.h>
    #include <42parser/lexer.h>


typedef struct {
    lexer_t lexer;
    token_t *current;
    token_t *next;
} parser_t;


// User entry:
ast_t *parse_input(const char *input);

// --------------- Parsing Pipeline --------------- :
// Parser grammar (highest to lowest precedence):
ast_t *parse_program(parser_t *parser);
ast_t *parse_statement(parser_t *parser);
ast_t *parse_expression(parser_t *parser);
ast_t *parse_atom(parser_t *parser);
ast_t *parse_subatom(parser_t *parser);

// Parser implementation:
ast_t *parse_binary_operation(parser_t *parser);
ast_t *parse_pipeline(parser_t *parser);
ast_t *parse_parenthesis(parser_t *parser);
ast_t *parse_command(parser_t *parser);
ast_t *parse_argument(parser_t *parser);
ast_t *parse_redirect_out(parser_t *parser);
ast_t *parse_redirect_append(parser_t *parser);
ast_t *parse_redirect_in(parser_t *parser);
ast_t *parse_redirect_non_fd(parser_t *parser, redirect_type_t type);

// ----------------- Parsing Utils ---------------- :
void parser_init(parser_t *parser, const char *input);
void parser_next(parser_t *parser);
void parser_term(parser_t *parser);


#endif
