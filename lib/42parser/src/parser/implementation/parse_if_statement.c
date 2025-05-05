/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_if_statement
*/

#include "42parser/token.h"
#include <42parser/parser.h>
#include <42parser/error.h>
#include <42parser/ast.h>
#include <stdlib.h>


/*
** If statement syntax error handler.
*/
static ast_t *syntax_error(ast_t *node, parser_errno_t error)
{
    parser_errno_set_weak(error);
    return node;
}

static bool is_body_end(const parser_t *parser)
{
    return
        parser->current->type == TT_ENDIF ||
        parser->current->type == TT_ERROR ||
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
    if (parser->current->type != TT_ENDIF)
        parser_errno_set(PE_MISSING_THEN_ENDIF);
    return node;
}

static bool is_condition_end(const parser_t *parser)
{
    return
        parser->current->type == TT_SEPARATOR ||
        parser->current->type == TT_ERROR ||
        parser->current->type == TT_EOF;
}

static void parse_command_condition(parser_t *parser, ast_t *node)
{
    ast_conditional_t *cond = node->data;
    ast_t *current;

    cond->is_command = true;
    cond->condition.command = parse_expression(parser);
    if (parser->current->type != TT_SEPARATOR)
        return parser_errno_set(PE_MISSING_THEN_ENDIF);
    while (parser->current->type == TT_SEPARATOR)
        parser_next(parser);
}

static void parse_test_condition(parser_t *parser, ast_t *node)
{
    ast_conditional_t *cond = node->data;
    ast_t *current;

    parser_next(parser);
    cond->is_command = false;
    cond->condition.test_args = ast_node_buffer_create();
    while (IS_ARGUMENT(parser->current->type)) {
        current = parse_subatom(parser);
        ast_node_buffer_append(cond->condition.test_args, current);
        if (current->type == AT_ERROR)
            break;
    }
    if (!parser_scan(parser, TT_RPAREN))
        return parser_errno_set(PE_UNMATCHED_RPAREN);
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
    ast_conditional_t *cond = calloc(1, sizeof(ast_conditional_t));

    node->data = cond;
    parser_next(parser);
    if (parser->current->type != TT_LPAREN)
        parse_command_condition(parser, node);
    else
        parse_test_condition(parser, node);
    if (!parser_scan(parser, TT_THEN))
        return syntax_error(node, PE_MISSING_THEN_ENDIF);
    cond->body = parse_body(parser);
    parser_next(parser);
    return node;
}
