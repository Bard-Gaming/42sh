/*
** EPITECH PROJECT, 2025
** Project - 42sh
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
    data->io_files[0] = 0;
    data->io_files[1] = 1;
    data->io_files[2] = 2;
    data->read_file = 0;
    data->write_file = 1;
    data->prev_subproc = -1;
    return data;
}
