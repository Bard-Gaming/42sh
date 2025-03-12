/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_data_create
*/

#include <mysh/data.h>
#include <unistd.h>
#include <stdlib.h>


sh_data_t *sh_data_create(void)
{
    sh_data_t *data = malloc(sizeof(sh_data_t));

    data->env = NULL;
    data->exit_status = 0;
    data->io_files[STDIN_FILENO] = STDIN_FILENO;
    data->io_files[STDOUT_FILENO] = STDOUT_FILENO;
    data->io_files[STDERR_FILENO] = STDERR_FILENO;
    return data;
}
