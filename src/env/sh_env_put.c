/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_env_put
*/

#include <mysh/env.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <stdlib.h>


static size_t get_delim_index(const char *value, char delim)
{
    for (size_t i = 0; value[i] != '\0'; i++) {
        if (value[i] == delim)
            return i;
    }
    sh_puterr("Programmer Error: invalid item_value for sh_env_put\n");
    exit(84);
}

static sh_env_item_t *get_existing_value(sh_env_t *env,
    const char *ref, size_t delim_index)
{
    for (size_t i = 0; i < env->count; i++) {
        if (sh_strncmp(env->items[i].variable, ref, delim_index) == 0)
            return &env->items[i];
    }
    return NULL;
}

static void replace_value(sh_env_item_t *item, char *value, size_t delim)
{
    free(item->variable);
    item->variable = value;
    item->value = value + delim + 1;
}

static void grow_env(sh_env_t *env)
{
    size_t new_capacity = env->capacity * SH_ENV_GROWTH_FACTOR;
    sh_env_item_t *item_buffer = malloc(new_capacity * sizeof(sh_env_item_t));

    for (size_t i = 0; i < env->count; i++)
        item_buffer[i] = env->items[i];
    free(env->items);
    env->items = item_buffer;
    env->capacity = new_capacity;
}

void sh_env_put(sh_env_t *env, const char *item_value)
{
    size_t delim_index = get_delim_index(item_value, '=');
    sh_env_item_t *location = get_existing_value(env, item_value, delim_index);
    char *value_duplicate = sh_strdup(item_value);

    value_duplicate[delim_index] = '\0';
    if (location != NULL)
        return replace_value(location, value_duplicate, delim_index);
    if (env->count == env->capacity)
        grow_env(env);
    env->items[env->count].variable = value_duplicate;
    env->items[env->count].value = value_duplicate + delim_index + 1;
    env->count++;
}
