/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_env_put
*/

#include <mysh/env.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <stdlib.h>


/*
** Gets the index in the given character string
** of the delimiter character. This is especially
** useful when separating the variable's name from
** its value.
**
** Example:
** get_delim_index("name=value", '=')
** would yield 4, since '=' is at the index 4.
*/
static size_t get_delim_index(const char *value, char delim)
{
    for (size_t i = 0; value[i] != '\0'; i++) {
        if (value[i] == delim)
            return i;
    }
    sh_puterr("Programmer Error: invalid item_value for sh_env_put\n");
    exit(84);
}

/*
** Retrieves a pointer to an existing item in
** the environment. Returns NULL if no existing
** item exists in the environment.
*/
static struct sh_env_item *get_existing_item(sh_env_t *env,
    const char *ref, size_t delim_index)
{
    for (size_t i = 0; i < env->count; i++) {
        if (sh_strncmp(env->items[i].variable, ref, delim_index) == 0)
            return &env->items[i];
    }
    return NULL;
}

/*
** Replaces the value of an existing environment
** variable by a new value.
*/
static void replace_value(struct sh_env_item *item, char *value, size_t delim)
{
    free(item->variable);
    item->variable = value;
    item->value = value + delim + 1;
}

/*
** Increases the amount of allocated memory in
** the shell's environment to allow for more
** items.
*/
static void grow_env(sh_env_t *env)
{
    size_t new_capacity = env->capacity * SH_ENV_GROWTH_FACTOR;
    struct sh_env_item *item_buffer = malloc(
        new_capacity * sizeof(struct sh_env_item)
    );

    for (size_t i = 0; i < env->count; i++)
        item_buffer[i] = env->items[i];
    free(env->items);
    env->items = item_buffer;
    env->capacity = new_capacity;
}

/*
** Puts an environment variable value into the
** given environment.
** This effectively adds a new environment variable
** to the environment if the given environment variable
** doesn't exist yet, and updates the value of the
** environment variable if it already exists.
*/
void sh_env_put(sh_env_t *env, const char *item_value)
{
    size_t delim_index = get_delim_index(item_value, '=');
    char *value_duplicate = sh_strdup(item_value);
    struct sh_env_item *existing_item = get_existing_item(
        env, item_value, delim_index
    );

    value_duplicate[delim_index] = '\0';
    if (existing_item != NULL)
        return replace_value(existing_item, value_duplicate, delim_index);
    if (env->count == env->capacity)
        grow_env(env);
    env->items[env->count].variable = value_duplicate;
    env->items[env->count].value = value_duplicate + delim_index + 1;
    env->count++;
}
