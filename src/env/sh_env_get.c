/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_get
*/

#include <mysh/env.h>
#include <mysh/string.h>


const char *sh_env_get(const sh_env_t *env, const char *name)
{
    for (size_t i = 0; i < env->count; i++) {
        if (sh_strcmp(env->items[i].variable, name) == 0)
            return env->items[i].value;
    }
    return NULL;
}
