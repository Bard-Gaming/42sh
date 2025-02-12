/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_env_unset
*/

#include <mysh/env.h>
#include <mysh/string.h>


static void remove_item(sh_env_t *env, size_t index)
{
    env->items[index] = env->items[env->count - 1];
    env->count--;
}

void sh_env_unset(sh_env_t *env, const char *name)
{
    for (size_t i = 0; i < env->count; i++) {
        if (sh_strcmp(env->items[i].variable, name) != 0)
            continue;
        remove_item(env, i);
        return;
    }
}
