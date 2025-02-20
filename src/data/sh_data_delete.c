/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_data_delete
*/

#include <mysh/data.h>
#include <mysh/env.h>
#include <stdlib.h>


/*
** Free structure and all of its containing data
*/
void sh_data_delete(sh_data_t *data)
{
    sh_env_delete(data->env);
    free(data->home_dir);
    free(data->previous_dir);
    free(data);
}
