/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_env
*/

#include <42sh/builtins.h>
#include <42sh/data.h>
#include <42sh/env.h>
#include <42sh/io.h>


/*
** Implementation for the shell's builtin
** env command.
** This command displays the shell's current
** environment by writing it to stdout in a
** specific format.
*/
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
