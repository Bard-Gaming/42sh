/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_mainloop
*/

#include <mysh/shell.h>
#include <mysh/arguments.h>
#include <stdio.h>


int shell_mainloop(char *env[])
{
    argument_buffer_t *args = NULL;
    char *lineptr = NULL;
    size_t linecap = 0;
    ssize_t read_count;

    (void)env;
    read_count = getline(&lineptr, &linecap, stdin);
    while (read_count >= 0) {
        argument_buffer_delete(args);
        args = argument_buffer_from_line(lineptr);
        read_count = getline(&lineptr, &linecap, stdin);
    }
    free(lineptr);
    return 0;
}
