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
** This is the same as the standard
** arguments' version, except that this
** doesn't handle double quotes or single
** quotes.
*/
static ast_t *get_current_node(const char **current, const char *end)
{
    switch (**current) {
    case '$':
        return parse_variable(current, end);
    case '`':
        return parse_substitution(current, end);
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

static const char *find_end(const char *start, const char *limit)
{
    start++;
    while (*start != '"' && start < limit)
        start++;
    return start;
}

/*
** Parses a format string.
*/
ast_t *parse_format_string(const char **current, const char *end)
{
    ast_t *node = ast_create(AT_ARGUMENT_STR);
    const char *new_end = find_end(*current, end);

    if (*new_end != '"') {
        parser_errno_set(PE_UNMATCHED_FORMAT_STRING);
        node->type = AT_ERROR;
        return node;
    }
    node->data = ast_argument_create();
    (*current)++;
    while (**current != '"')
        parse_argument_char(node->data, current, new_end);
    (*current)++;
    return node;
}
