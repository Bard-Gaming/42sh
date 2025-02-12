/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** arguments_parse_arg
*/

#include <mysh/arguments.h>
#include <mysh/string.h>
#include <stdbool.h>


static bool is_eol(char c)
{
    return c == '\n' || c == '\0';
}

static bool is_whitespace(char c)
{
    return c == ' ' || c == '\t';
}

static void skip_leading_whitespace(const char **ptr)
{
    while (!is_eol(**ptr) && is_whitespace(**ptr))
        (*ptr)++;
}

static char *parse_string(const char **ptr)
{
    char quote = **ptr;
    const char *start = *ptr + 1;
    size_t len = 0;

    while (!is_eol(start[len]) && start[len] != quote)
        len++;
    *ptr += len + 2;
    return sh_strndup(start, len);
}

static char *parse_normal_arg(const char **ptr)
{
    const char *start = *ptr;
    size_t len = 0;

    while (!is_eol(start[len]) && !is_whitespace(start[len]))
        len++;
    *ptr += len;
    return sh_strndup(start, len);
}

/*
** Parse a single argument from the given
** character buffer. The data behind the
** given buffer is unmodified, but the
** pointer to the data is set to after the
** newly parsed argument.
*/
char *arguments_parse_arg(const char **start)
{
    skip_leading_whitespace(start);
    if (is_eol(**start))
        return NULL;
    if (**start == '\'' || **start == '"')
        return parse_string(start);
    return parse_normal_arg(start);
}
