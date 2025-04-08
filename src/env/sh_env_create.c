/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_create
*/

#include <42sh/data.h>
#include <42sh/symbols.h>
#include <stdlib.h>
#include <string.h>


/*
** Duplicates a variable from a given symbol
** bucket. The duplicate is formatted in the
** following way:
** <var>=<value>
*/
static char *duplicate_variable(struct sh_symbol_bucket *bucket)
{
    size_t variable_len = strlen(bucket->name) + strlen(bucket->value) + 1;
    char *variable = malloc((variable_len + 1) * sizeof(char));
    char *current = variable;

    current = stpcpy(current, bucket->name);
    *current = '=';
    current = stpcpy(current + 1, bucket->value);
    return variable;
}

/*
** Turns the shell's environment symbol
** table to a unix environment, i.e.
** a string array terminated by NULL.
** The given environment should be
** freed using the sh_data_del_unix_env
** function.
*/
char **sh_env_create(const sh_data_t *data)
{
    char **unix_env = malloc((data->env->count + 1) * sizeof(char *));
    struct sh_symbol_bucket *bucket;
    size_t var_index = 0;

    for (size_t i = 0; i < data->env->capacity; i++) {
        if (data->env->data[i].name == NULL)
            continue;
        bucket = data->env->data + i;
        unix_env[var_index] = duplicate_variable(bucket);
        var_index++;
    }
    unix_env[data->env->count] = NULL;
    return unix_env;
}
