/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_if_statement
*/

#include <42parser/parser.h>
#include <42parser/error.h>
#include <42parser/ast.h>
#include <stdlib.h>


/*
** Tells whether or not the parser's current
** token is a body's end token or not.
*/
static bool is_body_end(const parser_t *parser)
{
    return
        parser->current->type == TT_ENDIF ||
        parser->current->type == TT_ERROR ||
        parser->current->type == TT_ELSE ||
        parser->current->type == TT_EOF;
}

/*
** Parses an if condition's body.
** This body is similar to a program node,
** with the exception that it is bounded by
** the endif statement.
*/
static ast_t *parse_body(parser_t *parser)
{
    ast_t *node = ast_create(AT_PROGRAM);
    ast_node_buffer_t *prog = ast_node_buffer_create();
    ast_t *current_stmt;

    node->data = prog;
    do {
        while (parser->current->type == TT_SEPARATOR)
            parser_next(parser);
        if (is_body_end(parser))
            break;
        current_stmt = parse_statement(parser);
        ast_node_buffer_append(prog, current_stmt);
        if (current_stmt->type == AT_ERROR)
            return node;
    } while (parser->current->type == TT_SEPARATOR);
    return node;
}

/*
** Parses a command condition.
** Command conditions are built as follows:
** <expression> <sep>+
** (the separator is required to differenciate
** it from the "then" token).
*/
static ast_t *parse_command_condition(parser_t *parser)
{
    ast_t *command = parse_expression(parser);

    if (parser->current->type != TT_SEPARATOR)
        parser_errno_set(PE_MISSING_THEN_ENDIF);
    while (parser->current->type == TT_SEPARATOR)
        parser_next(parser);
    return command;
}

/*
** Parses a test condition.
** Test conditions are built as follows:
** "(" <arg>+ ")"
*/
static ast_node_buffer_t *parse_test_condition(parser_t *parser)
{
    ast_node_buffer_t *args = ast_node_buffer_create();
    ast_t *current;

    parser_next(parser);
    while (IS_ARGUMENT(parser->current->type)) {
        current = parse_subatom(parser);
        ast_node_buffer_append(args, current);
        if (current->type == AT_ERROR)
            break;
    }
    if (!parser_scan(parser, TT_RPAREN))
        parser_errno_set(PE_UNMATCHED_RPAREN);
    return args;
}

static void parse_substatement(parser_t *parser, ast_if_stmnt_t *data)
{
    ast_node_buffer_t *test = NULL;
    ast_t *command = NULL;
    ast_t *body;

    parser_next(parser);
    if (parser->current->type == TT_LPAREN)
        test = parse_test_condition(parser);
    else
        command = parse_command_condition(parser);
    if (!parser_scan(parser, TT_THEN))
        parser_errno_set_weak(PE_MISSING_THEN_ENDIF);
    body = parse_body(parser);
    if (test != NULL)
        ast_if_stmnt_add_test(data, test, body);
    else
        ast_if_stmnt_add_command(data, command, body);
    if (parser->current->type == TT_ELSE && parser->next->type == TT_IF)
        parser_next(parser);
}

/*
** Parses an if statement.
** If statements are built as follows:
**
** -----------------------------------
** "if" "(" <args> ")" "then"
**     <body>
** "endif"
** -----------------------------------
** "if" <expr> <sep> "then"
**     <body>
** "endif"
** -----------------------------------
**
** Note: indentation is optional.
*/
ast_t *parse_if_statement(parser_t *parser)
{
    ast_t *node = ast_create(AT_IF_STATEMENT);
    ast_if_stmnt_t *data = ast_if_stmnt_create();

    node->data = data;
    while (parser->current->type == TT_IF)
        parse_substatement(parser, data);
    if (parser->current->type == TT_ELSE) {
        parser_next(parser);
        data->bodies[data->count] = parse_body(parser);
    }
    if (!parser_scan(parser, TT_ENDIF))
        parser_errno_set_weak(PE_MISSING_THEN_ENDIF);
    return node;
}
