/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
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
