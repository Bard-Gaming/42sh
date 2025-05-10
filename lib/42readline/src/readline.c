/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline
*/

#include <readline.h>
#include <readline/terminal.h>
#include <readline/internal.h>


char *readline(int fd)
{
    char *result;

    *rl_state_get() = true;
    result = isatty(fd) ?
        rl_terminal_readline(fd) : rl_readline_file(fd);
    *rl_state_get() = false;
    return result;
}
