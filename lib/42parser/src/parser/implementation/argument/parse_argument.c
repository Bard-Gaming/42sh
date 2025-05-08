/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_argument
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/token.h>
#include <string.h>
#include <stdlib.h>


/*
** Parses the appropriate node.
** Returns NULL if the given character
** doesn't correspond to any node.
*/
static ast_t *get_current_node(const char **current, const char *end)
{
    switch (**current) {
    case '$':
        return parse_variable(current, end);
    case '`':
        return parse_substitution(current, end);
    case '"':
        return parse_format_string(current, end);
    case '\'':
        return parse_raw_string(current, end);
    default:
        return NULL;
    }
}

/*
** Processes any given character within the argument.
*/
static void parse_argument_char(ast_argument_t *arg,
    const char **current, const char *end)
{
    ast_t *node = get_current_node(current, end);

    if (node != NULL)
        return ast_argument_add_node(arg, node);
    ast_argument_add_char(arg, **current);
    (*current)++;
}

/*
** Parses an argument, which includes
** parsing variables.
*/
ast_t *parse_argument(parser_t *parser)
{
    ast_t *node = ast_create(AT_ARGUMENT);
    const char *end = parser->current->start + parser->current->length;
    const char *current = parser->current->start;

    parser_next(parser);
    node->data = ast_argument_create();
    while (current < end)
        parse_argument_char(node->data, &current, end);
    return node;
}
