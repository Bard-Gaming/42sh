/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_substitution
*/

#include "42parser/ast.h"
#include <42parser/parser.h>
#include <42parser/error.h>
#include <string.h>
#include <stdlib.h>


static ast_t *unmatched_backtick_error(void)
{
    parser_errno_set(PE_UNMATCHED_BACKTICK);
    return ast_create(AT_ERROR);
}

/*
** Parses the AST that is contained within
** the command substitution.
*/
static ast_t *parse_substitution_ast(const char **current, const char *start)
{
    char *input = strndup(start, *current - start - 1);
    ast_t *result;

    if (input == NULL)
        return NULL;
    result = parse_input(input);
    free(input);
    return result;
}

/*
** Parses a substitution within an argument.
*/
ast_t *parse_substitution(const char **current, const char *end)
{
    const char *start = *current + 1;
    ast_t *node;

    (*current)++;
    while (**current != '`' && *current < end)
        (*current)++;
    if (**current != '`')
        return unmatched_backtick_error();
    (*current)++;
    node = ast_create(AT_SUBSTITUTION);
    node->data = parse_substitution_ast(current, start);
    if (node->data == NULL)
        node->type = AT_ERROR;
    return node;
}
