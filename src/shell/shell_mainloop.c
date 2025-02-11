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
#include <unistd.h>
#include <stdio.h>


int shell_mainloop(char *env[])
{
    argument_buffer_t *args = NULL;
    char *lineptr = NULL;
    size_t linecap = 0;
    ssize_t read_count;
    unsigned char exit_status = 0;

    read_count = shell_query_command(&lineptr, &linecap, stdin);
    while (read_count >= 0) {
        argument_buffer_delete(args);
        args = argument_buffer_from_line(lineptr);
        if (args->count != 0)
            exit_status = shell_execline(args->data, env);
        read_count = shell_query_command(&lineptr, &linecap, stdin);
    }
    argument_buffer_delete(args);
    free(lineptr);
    if (isatty(0))
        sh_putstr("\n");
    return exit_status;
}
