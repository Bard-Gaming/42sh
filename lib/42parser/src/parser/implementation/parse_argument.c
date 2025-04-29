/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_argument
*/

#include "42parser/error.h"
#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/token.h>
#include <string.h>
#include <stdlib.h>


static bool is_variable_char(char c)
{
    return
        ('a' <= c && c <= 'z') ||
        ('A' <= c && c <= 'Z') ||
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

static void handle_bracket_start(const char **current, bool *is_bracket)
{
    *is_bracket = true;
    (*current)++;
}

static bool handle_bracket_end(const char **current, const char *start)
{
    if (**current != '}') {
        parser_errno_set(PE_UNMATCHED_RBRACKET);
        return false;
    }
    if (*current - start == 0) {
        parser_errno_set(PE_ILLEGAL_VAR_NAME);
        return false;
    }
    return true;
}

static void parse_variable(ast_argument_t *arg,
    const char **current, const char *end)
{
    const char *start;
    bool is_bracket = false;
    ast_t *node;

    (*current)++;
    if (**current == '{')
        handle_bracket_start(current, &is_bracket);
    start = *current;
    if (**current != '?' && **current != '}' && !is_variable_char(**current))
        return ast_argument_add_char(arg, '$');
    while (*current < end && **current != '?' && is_variable_char(**current))
        (*current)++;
    if (is_bracket && !handle_bracket_end(current, start))
        return;
    node = ast_create(AT_VARIABLE);
    ast_argument_add_node(arg, node);
    node->data = strndup(start, *current - start);
    if (is_bracket)
        (*current)++;
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
