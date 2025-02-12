/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_env
*/

#include <mysh/builtins.h>
#include <mysh/env.h>
#include <mysh/io.h>


int builtin_env(const char *args[], sh_env_t *env)
{
    size_t name_len;

    if (args[1] != NULL) {
        sh_puterr("env: Too many arguments.\n");
        return 84;
    }
    for (size_t i = 0; i < env->count; i++) {
        name_len = env->items[i].value - env->items[i].variable - 1;
        env->items[i].variable[name_len] = '=';
        sh_putstr(env->items[i].variable);
        sh_putstr("\n");
        env->items[i].variable[name_len] = '\0';
    }
    return 0;
}
