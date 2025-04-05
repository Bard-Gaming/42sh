/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_delete
*/

#include <mysh/env.h>
#include <stdlib.h>


/*
** Delete the given environment structure
** and free all of its containing memory.
** Does nothing if the given ptr is NULL.
*/
void sh_env_delete(sh_env_t *env)
{
    if (env == NULL)
        return;
    for (size_t i = 0; i < env->count; i++)
        free(env->items[i].variable);
    free(env->items);
    free(env);
}
