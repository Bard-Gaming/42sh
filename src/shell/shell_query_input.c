/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_query_input
*/

#include <42sh/shell.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <readline.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


static bool is_whitespace(char c)
{
    return
        c == '\t' ||
        c == '\n' ||
        c == ' ';
}

/*
** Returns a string without any whitespace
** at the end.
*/
static char *get_stripped(const char *str)
{
    char *start = sh_strdup(str);
    char *end = start + strlen(start) - 1;

    while (end > start && is_whitespace(*end))
        end--;
    *(end + 1) = '\0';
    return start;
}

/*
** Tells whether or not a given string
** is new, i.e. if it is different from
** the previously saved line.
*/
static bool is_new_command(const char *str)
{
    char *prev_line = shell_history_get(1);
    bool is_equal;

    if (prev_line == NULL)
        return true;
    is_equal = strcmp(str, prev_line) != 0;
    free(prev_line);
    return is_equal;
}

static bool contains_new_content(const char *str)
{
    char *stripped = get_stripped(str);
    bool is_new;

    if (*stripped == '\0') {
        free(stripped);
        return false;
    }
    is_new = is_new_command(stripped);
    free(stripped);
    return is_new;
}

/*
** Query the user for input.
** Displays a visual prompt if
** the input is a TTY.
** The input is retrieved via the
** readline() function of the readline
** library (see lib/42readline).
*/
char *shell_query_input(sh_data_t *data)
{
    char *input = readline(0, data->prompt_str);

    if (input == NULL)
        return NULL;
    if (isatty(0) && contains_new_content(input))
        shell_history_add(input);
    return input;
}
