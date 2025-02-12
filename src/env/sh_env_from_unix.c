/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_env_from_unix
*/

#include <mysh/env.h>
#include <mysh/string.h>


sh_env_t *sh_env_from_unix(const char **unix_env)
{
    sh_env_t *env = sh_env_create();

    while (*unix_env != NULL) {
        sh_env_put(env, *unix_env);
        unix_env++;
    }
    return env;
}
