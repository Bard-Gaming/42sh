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


static bool is_var_char(char c)
{
    return
        ('0' <= c && c <= '9') ||
        ('A' <= c && c <= 'Z') ||
        ('a' <= c && c <= 'z') ||
        c == '_';
}

static void parse_var(ast_argument_t *arg,
    const char **current, const char *end)
{
    size_t var_len = 0;
    const char *start = *current + 1;

    (*current)++;
    if (!is_var_char(**current)) {
        ast_argument_add_char(arg, '$');
        return;
    }
    while (*current < end && is_var_char(**current)) {
        (*current)++;
        var_len++;
    }
    ast_argument_add_variable(arg, strndup(start, var_len));
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
    while (current < end) {
        if (*current == '$') {
            parse_var(node->data, &current, end);
            continue;
        }
        ast_argument_add_char(node->data, *current);
        current++;
    }
    return node;
}
