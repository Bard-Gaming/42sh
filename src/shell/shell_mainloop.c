/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_mainloop
*/

#include <mysh/shell.h>
#include <mysh/arguments.h>
#include <mysh/data.h>
#include <mysh/io.h>
#include <unistd.h>
#include <stdio.h>


int shell_mainloop(sh_data_t *data)
{
    argument_buffer_t *args = NULL;
    char *lineptr = NULL;
    size_t linecap = 0;
    ssize_t read_count;

    read_count = shell_query_command(&lineptr, &linecap);
    while (read_count > 0) {
        argument_buffer_delete(args);
        args = argument_buffer_from_line(lineptr);
        if (args->count != 0)
            data->exit_status = shell_execline(args->data, data);
        read_count = shell_query_command(&lineptr, &linecap);
    }
    argument_buffer_delete(args);
    free(lineptr);
    if (isatty(0))
        sh_putstr("\n");
    return data->exit_status;
}
