/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_data_delete
*/

#include <mysh/data.h>
#include <mysh/env.h>
#include <stdlib.h>


/*
** Delete the given shell data structure
** and free all of its containing memory.
** Does nothing if the given ptr is NULL.
*/
void sh_data_delete(sh_data_t *data)
{
    if (data == NULL)
        return;
    sh_env_delete(data->env);
    free(data->home_dir);
    free(data->previous_dir);
    free(data);
}
