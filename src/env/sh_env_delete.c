/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_env_delete
*/

#include <mysh/env.h>
#include <stdlib.h>


void sh_env_delete(sh_env_t *env)
{
    for (size_t i = 0; i < env->count; i++)
        free(env->items[i].variable);
    free(env->items);
    free(env);
}
