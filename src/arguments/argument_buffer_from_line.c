/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** argument_buffer_from_line
*/

#include <mysh/arguments.h>
#include <stdbool.h>


static bool is_whitespace(char c)
{
    return
        c == ' ' ||
        c == '\t';
}

/*
** Returns whether a character
** is an end of line (EOL) character
** or not
*/
static bool is_eol(char c)
{
    return
        c == '\n' ||
        c == '\0';
}

static void skip_leading_whitespace(const char **ptr)
{
    while (!is_eol(**ptr) && is_whitespace(**ptr))
        (*ptr)++;
}

/*
** Create an argument buffer from a
** line of arguments
*/
argument_buffer_t *argument_buffer_from_line(const char *line)
{
    argument_buffer_t *buf = argument_buffer_create();
    const char *current;

    skip_leading_whitespace(&line);
    current = line;
    while (!is_eol(*current)) {
        while (!is_eol(*current) && !is_whitespace(*current))
            current++;
        argument_buffer_appendn(buf, line, (size_t)(current - line));
        while (is_whitespace(*current))
            current++;
        line = current;
    }
    return buf;
}
