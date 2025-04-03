/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_delete_unix
*/

#include <mysh/env.h>
#include <stdlib.h>


void sh_env_delete_unix(char **env)
{
    char **current = env;

    while (*current != NULL) {
        free(*current);
        current++;
    }
    free(env);
}
