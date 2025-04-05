/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_delete_unix
*/

#include <mysh/env.h>
#include <stdlib.h>


/*
** Delete the given unix-style environment
** variable array.
** This function should only be used on arrays
** created by the sh_env_to_unix() function.
** Does nothing if the given ptr is NULL.
*/
void sh_env_delete_unix(char **env)
{
    char **current = env;

    if (env == NULL)
        return;
    while (*current != NULL) {
        free(*current);
        current++;
    }
    free(env);
}
