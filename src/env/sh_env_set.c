/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_env_set
*/

#include <mysh/env.h>
#include <mysh/string.h>


void sh_env_set(sh_env_t *env, const char *name, const char *value)
{
    size_t name_len = sh_strlen(name);
    size_t value_len = sh_strlen(value);
    char *item_value = malloc((name_len + value_len + 2) * sizeof(char));

    item_value[name_len] = '=';
    sh_strcpy(item_value, name);
    sh_strcpy(item_value + name_len + 1, value);
    item_value[name_len + value_len + 1] = '\0';
    sh_env_put(env, item_value);
    free(item_value);
}
