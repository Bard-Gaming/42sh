/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_raw_string
*/

#include <42parser/parser.h>
#include <string.h>


/*
** Parses a raw string.
*/
ast_t *parse_raw_string(const char **current, const char *end)
{
    ast_t *node = ast_create(AT_RAW_ARGUMENT);
    const char *start = *current + 1;

    (*current)++;
    while (**current != '\'' && *current < end)
        (*current)++;
    (*current)++;
    node->data = strndup(start, *current - start - 1);
    if (node->data == NULL)
        node->type = AT_ERROR;
    return node;
}
