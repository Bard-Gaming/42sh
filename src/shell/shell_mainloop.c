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
    char *command = shell_query_command();

    while (command != NULL) {
        argument_buffer_delete(args);
        args = argument_buffer_from_line(command);
        free(command);
        if (args->count != 0)
            data->exit_status = shell_execline(args->data, data);
        command = shell_query_command();
    }
    argument_buffer_delete(args);
    if (isatty(0))
        sh_putstr("\n");
    return data->exit_status;
}
