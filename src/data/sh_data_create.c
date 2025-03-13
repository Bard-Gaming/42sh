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
    data->cmd_state = CS_NORMAL;
    data->pipe_read = -1;
    data->pipe_write = -1;
    return data;
}
