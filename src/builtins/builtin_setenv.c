/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_setenv
*/

#include <mysh/builtins.h>
#include <mysh/env.h>
#include <mysh/io.h>


int builtin_setenv(const char *args[], sh_env_t *env)
{
    if (args[1] == NULL)
        return builtin_env(args, env);
    if (args[2] != NULL && args[3] != NULL) {
        sh_puterr("setenv: Too many arguments.\n");
        return 84;
    }
    sh_env_set(env, args[1], args[2] == NULL ? "" : args[2]);
    return 0;
}
