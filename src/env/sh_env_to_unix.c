/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_to_unix
*/

#include <mysh/env.h>
#include <mysh/string.h>
#include <stdlib.h>


/*
** Duplicates an item's value into a new
** string array, in the 'name=value' format.
*/
char *dupe_item_value(const struct sh_env_item *item)
{
    size_t delim_index = sh_strlen(item->variable);
    size_t len = delim_index + sh_strlen(item->value) + 1;
    char *value = malloc((len + 1) * sizeof(char));

    value[len] = '\0';
    for (size_t i = 0; i < len; i++)
        value[i] = item->variable[i];
    value[delim_index] = '=';
    return value;
}

/*
** Turns a shell environment pointer to a
** unix-style environment array (like the 'environ' global).
** This array should then be freed using the
** sh_env_delete_unix() function.
*/
char **sh_env_to_unix(const sh_env_t *env)
{
    char **unix_env = malloc((env->count + 1) * sizeof(char *));

    unix_env[env->count] = NULL;
    for (size_t i = 0; i < env->count; i++)
        unix_env[i] = dupe_item_value(&env->items[i]);
    return unix_env;
}
