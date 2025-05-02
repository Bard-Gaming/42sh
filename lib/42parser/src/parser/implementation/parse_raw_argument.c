/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_raw_argument
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/token.h>


ast_t *parse_raw_argument(parser_t *parser)
{
    ast_t *node = ast_create(AT_RAW_ARGUMENT);

    node->data = token_value(parser->current);
    parser_next(parser);
    return node;
}
