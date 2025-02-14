/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_env_create
*/

#include <mysh/env.h>
#include <stdlib.h>


sh_env_t *sh_env_create(void)
{
    sh_env_t *env = malloc(sizeof(sh_env_t));

    env->capacity = SH_ENV_INITIAL_CAPACITY;
    env->count = 0;
    env->items = malloc(SH_ENV_INITIAL_CAPACITY * sizeof(struct sh_env_item));
    return env;
}
