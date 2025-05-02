/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_query_input
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <readline.h>
#include <unistd.h>


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
    if (isatty(0))
        sh_putstr(data->prompt_str);
    return readline(0);
}
