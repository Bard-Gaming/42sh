/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_query_input
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <readline.h>
#include <unistd.h>


static bool is_whitespace(char c)
{
    return
        c == '\t' ||
        c == '\n' ||
        c == ' ';
}

/*
** Tells whether or not a given string
** contains any sort of usable content or
** not, i.e. if the string isn't just blank.
*/
static bool contains_content(const char *str)
{
    if (str == NULL)
        return false;
    while (*str != '\0') {
        if (!is_whitespace(*str))
            return true;
        str++;
    }
    return false;
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

    if (isatty(0) && contains_content(input))
        shell_history_add(input);
    return input;
}
