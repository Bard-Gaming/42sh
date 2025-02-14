/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** shell_init
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/env.h>


sh_data_t *shell_init(char *env[])
{
    sh_data_t *shell_data = sh_data_create();

    shell_data->env = sh_env_from_unix((const char **)env);
    return shell_data;
}
