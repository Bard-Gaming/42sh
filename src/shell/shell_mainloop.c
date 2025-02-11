/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_mainloop
*/

#include <mysh/shell.h>
#include <mysh/arguments.h>
#include <mysh/io.h>
#include <stdio.h>


static ssize_t query_command(char **restrict lineptr,
    size_t *restrict n, FILE *restrict stream)
{
    sh_putstr("$> ");
    return getline(lineptr, n, stream);
}

int shell_mainloop(char *env[])
{
    argument_buffer_t *args = NULL;
    char *lineptr = NULL;
    size_t linecap = 0;
    ssize_t read_count;

    (void)env;
    read_count = query_command(&lineptr, &linecap, stdin);
    while (read_count >= 0) {
        argument_buffer_delete(args);
        args = argument_buffer_from_line(lineptr);
        if (args->count != 0)
            shell_execline(args->data, env);
        read_count = query_command(&lineptr, &linecap, stdin);
    }
    free(lineptr);
    return 0;
}
