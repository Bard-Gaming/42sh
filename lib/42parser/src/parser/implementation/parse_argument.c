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


static bool is_variable_char(char c)
{
    return
        ('a' <= c && c <= 'z') ||
        ('Z' <= c && c <= 'Z') ||
        ('0' <= c && c <= '9') ||
        (c == '_');
}

static void unmatched_substitution_error(void)
{
    parser_errno_set(PE_UNMATCHED_BACKTICK);
}

static void parse_substitution(ast_argument_t *arg,
    const char **current, const char *end)
{
    const char *start = *current + 1;
    char *input;
    ast_t *node;

    (*current)++;
    while (*current < end && **current != '`')
        (*current)++;
    if (*current == end)
        return unmatched_substitution_error();
    input = strndup(start, *current - start);
    (*current)++;
    node = parse_input(input);
    if (node != NULL)
        ast_argument_add_node(arg, node);
    free(input);
}

static void parse_variable(ast_argument_t *arg,
    const char **current, const char *end)
{
    ast_t *node;
    const char *start;

    (*current)++;
    start = *current;
    if (**current != '?' && !is_variable_char(**current))
        return ast_argument_add_char(arg, '$');
    node = ast_create(AT_VARIABLE);
    ast_argument_add_node(arg, node);
    if (**current == '?') {
        node->data = strdup("?");
        (*current)++;
        return;
    }
    while (*current < end && is_variable_char(**current))
        (*current)++;
    node->data = strndup(start, *current - start);
}

static void parse_arg_char(ast_argument_t *arg,
    const char **current, const char *end)
{
    if (**current == '$')
        return parse_variable(arg, current, end);
    if (**current == '`')
        return parse_substitution(arg, current, end);
    ast_argument_add_char(arg, **current);
    (*current)++;
}

/*
** Parses an argument, which includes
** parsing variables.
*/
ast_t *parse_argument(parser_t *parser)
{
    ast_t *node = ast_create(AST_ARG_TYPE(parser->current->type));
    const char *end = parser->current->start + parser->current->length;
    const char *current = parser->current->start;

    parser_next(parser);
    node->data = ast_argument_create();
    while (current < end)
        parse_arg_char(node->data, &current, end);
    return node;
}
