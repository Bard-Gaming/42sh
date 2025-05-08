/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_while_statement
*/

#include <42parser/parser.h>
#include <42parser/error.h>
#include <42parser/ast.h>
#include <stdlib.h>


/*
** Updates the given node to be an
** error node, sets the proper error,
** and returns the error node.
*/
static ast_t *no_args_error(ast_t *node)
{
    node->type = AT_ERROR;
    parser_errno_set(PE_WHILE_NO_ARGS);
    return node;
}

/*
** End of while statement's body.
*/
static bool is_body_end(const parser_t *parser)
{
    return
        token_match(parser->current, "end") ||
        parser->current->type == TT_ERROR ||
        parser->current->type == TT_EOF;
}

/*
** Parses a while statement's body.
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
** Creates a while statement pointer in
** a memory-safe way.
*/
static ast_while_loop_t *create_node_data(ast_condition_t *condition)
{
    ast_while_loop_t *data = malloc(sizeof(ast_while_loop_t));

    if (data == NULL)
        parser_critical_error();
    data->condition = *condition;
    data->body = NULL;
    return data;
}

/*
** Parses a while statement.
** While statements are built as follows:
**
** "while" <condition>
**     <body>
** "end"
*/
ast_t *parse_while_loop(parser_t *parser)
{
    ast_t *node = ast_create(AT_WHILE_LOOP);
    ast_condition_t condition;

    parser_next(parser);
    condition = parse_condition(parser);
    if (P_ERRNO == PE_UNMATCHED_RPAREN)
        return no_args_error(node);
    if (P_ERRNO == PE_UNMATCHED_LBRACE)
        parser_errno_set(PE_WHILE_MISSING_BRACE);
    node->data = create_node_data(&condition);
    if (P_ERRNO == PE_NONE)
        ((ast_while_loop_t *)node->data)->body = parse_body(parser);
    if (!parser_scan_keyword(parser, "end"))
        parser_errno_set_weak(PE_WHILE_MISSING_END);
    return node;
}
