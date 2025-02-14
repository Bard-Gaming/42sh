/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_unsetenv
*/

#include <mysh/builtins.h>
#include <mysh/data.h>
#include <mysh/env.h>
#include <mysh/io.h>
#include <stddef.h>


int builtin_unsetenv(const char *args[], sh_data_t *data)
{
    if (args[1] == NULL) {
        sh_puterr("unsetenv: Too few arguments.\n");
        return 84;
    }
    args++;
    while (*args != NULL) {
        sh_env_unset(data->env, *args);
        args++;
    }
    return 0;
}
