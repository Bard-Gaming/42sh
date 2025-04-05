/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_unset
*/

#include <mysh/env.h>
#include <mysh/string.h>


/*
** Removes an item using a simple
** swap-and-pop.
*/
static void remove_item(sh_env_t *env, size_t index)
{
    free(env->items[index].variable);
    env->items[index] = env->items[env->count - 1];
    env->count--;
}

/*
** Deletes an item specified by the given name
** from the given environment.
*/
void sh_env_unset(sh_env_t *env, const char *name)
{
    for (size_t i = 0; i < env->count; i++) {
        if (sh_strcmp(env->items[i].variable, name) != 0)
            continue;
        remove_item(env, i);
        return;
    }
}
