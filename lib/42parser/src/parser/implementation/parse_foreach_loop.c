/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_foreach_loop
*/

#include <42parser/parser.h>
#include <42parser/error.h>
#include <stdlib.h>


static ast_foreach_loop_t *create_data(void)
{
    ast_foreach_loop_t *data = malloc(sizeof(ast_foreach_loop_t));

    if (data == NULL)
        parser_critical_error();
    return data;
}

static ast_t *syntax_error(ast_t *node)
{
    parser_errno_set(PE_FOREACH_NO_ARGS);
    node->type = AT_ERROR;
    return node;
}

static ast_node_buffer_t *list_syntax_error(parser_errno_t error,
    ast_node_buffer_t *buffer)
{
    parser_errno_set(error);
    return buffer;
}

/*
** End of foreach loop's body.
*/
static bool is_body_end(const parser_t *parser)
{
    return
        token_match(parser->current, "end") ||
        parser->current->type == TT_ERROR ||
        parser->current->type == TT_EOF;
}

/*
** Parses a foreach loop's body.
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

static ast_node_buffer_t *parse_list(parser_t *parser)
{
    ast_node_buffer_t *buffer = ast_node_buffer_create();
    ast_t *argument;

    if (!parser_scan(parser, TT_LPAREN))
        return list_syntax_error(PE_UNMATCHED_RPAREN, buffer);
    while (IS_ARGUMENT(parser->current->type)) {
        argument = parse_subatom(parser);
        ast_node_buffer_append(buffer, argument);
        if (argument->type == AT_ERROR)
            return buffer;
    }
    if (!parser_scan(parser, TT_RPAREN))
        return list_syntax_error(PE_UNMATCHED_LPAREN, buffer);
    return buffer;
}

/*
** Parses a foreach loop.
** Foreach loops are built as follows:
** "foreach" <arg> "(" <args> ")"
**     <body>
** "end"
*/
ast_t *parse_foreach_loop(parser_t *parser)
{
    ast_t *node = ast_create(AT_FOREACH_LOOP);
    ast_foreach_loop_t *data;

    parser_next(parser);
    if (!IS_ARGUMENT(parser->current->type))
        return syntax_error(node);
    data = create_data();
    node->data = data;
    data->variable = parse_subatom(parser);
    data->list = parse_list(parser);
    data->body = parse_body(parser);
    if (!parser_scan_keyword(parser, "end"))
        parser_errno_set_weak(PE_FOREACH_MISSING_END);
    return node;
}
