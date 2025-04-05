/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_create
*/

#include <mysh/env.h>
#include <stdlib.h>


/*
** Allocates a new environment structure
** and initializes it with its default
** values.
** The returned pointer should be freed
** using the sh_env_delete() function.
** This function returns NULL if there
** isn't enough memory to allocate
** the required memory.
*/
sh_env_t *sh_env_create(void)
{
    sh_env_t *env = malloc(sizeof(sh_env_t));

    if (env == NULL)
        return NULL;
    env->capacity = SH_ENV_INITIAL_CAPACITY;
    env->count = 0;
    env->items = malloc(SH_ENV_INITIAL_CAPACITY * sizeof(struct sh_env_item));
    if (env->items == NULL) {
        free(env);
        return NULL;
    }
    return env;
}
