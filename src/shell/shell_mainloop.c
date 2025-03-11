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


void shell_mainloop(sh_data_t *data)
{
    argument_buffer_t *args = NULL;
    char *raw_input = shell_query_input();

    while (raw_input != NULL) {
        argument_buffer_delete(args);
        args = argument_buffer_from_line(raw_input);
        free(raw_input);
        if (args->count != 0)
            data->exit_status = shell_exec_command(args->data, data);
        raw_input = shell_query_input();
    }
    argument_buffer_delete(args);
    if (isatty(0))
        sh_putstr("\n");
}
