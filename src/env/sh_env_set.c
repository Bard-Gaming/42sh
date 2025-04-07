/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_set
*/

#include <42sh/env.h>
#include <string.h>
#include <stdlib.h>


/*
** Sets the environment variable of the given
** name to the given value. Both the name and
** value aren't modified, and are copied into
** the environment.
*/
void sh_env_set(sh_env_t *env, const char *name, const char *value)
{
    size_t name_len = strlen(name);
    size_t value_len = strlen(value);
    char *item_value = malloc((name_len + value_len + 2) * sizeof(char));

    strcpy(item_value, name);
    strcpy(item_value + name_len + 1, value);
    item_value[name_len] = '=';
    item_value[name_len + value_len + 1] = '\0';
    sh_env_put(env, item_value);
    free(item_value);
}
