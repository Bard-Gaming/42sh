/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_env
*/

#include <mysh/builtins.h>
#include <mysh/data.h>
#include <mysh/env.h>
#include <mysh/io.h>


int builtin_env(char *args[], sh_data_t *data)
{
    sh_env_t *env = data->env;
    size_t name_len;

    if (args[1] != NULL) {
        sh_puterr("env: Too many arguments.\n");
        return 84;
    }
    for (size_t i = 0; i < data->env->count; i++) {
        name_len = env->items[i].value - env->items[i].variable - 1;
        env->items[i].variable[name_len] = '=';
        sh_putstr(env->items[i].variable);
        sh_putstr("\n");
        env->items[i].variable[name_len] = '\0';
    }
    return 0;
}
