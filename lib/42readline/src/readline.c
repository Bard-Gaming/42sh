/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline
*/

#include <readline.h>
#include <readline/internal.h>


char *readline(int fd, const char *prompt)
{
    char *result;

    *rl_state_get() = true;
    result = isatty(fd) ?
        rl_readline_tty(fd, prompt) : rl_readline_file(fd);
    *rl_state_get() = false;
    return result;
}
