/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** argument_buffer_append
*/

#include <mysh/arguments.h>
#include <mysh/string.h>


static void grow_buffer(argument_buffer_t *buffer)
{
    size_t new_capacity = buffer->capacity * SH_AB_GROWTH_FACTOR;
    char **new_data = malloc(new_capacity * sizeof(char *));

    for (size_t i = 0; i < buffer->count; i++)
        new_data[i] = buffer->data[i];
    free(buffer->data);
    buffer->data = new_data;
    buffer->capacity = new_capacity;
}

/*
** Appends a copy of the given
** argument to the argument buffer
*/
void argument_buffer_append(argument_buffer_t *buffer, const char *arg)
{
    if (buffer->count == buffer->capacity)
        grow_buffer(buffer);
    buffer->data[buffer->count] = sh_strdup(arg);
    buffer->data[buffer->count + 1] = NULL;
    buffer->count++;
}

/*
** Appends a copy of the given argument,
** up to the end, to the argument buffer
*/
void argument_buffer_appendn(argument_buffer_t *buffer,
    const char *arg, size_t end)
{
    if (buffer->count == buffer->capacity)
        grow_buffer(buffer);
    buffer->data[buffer->count] = sh_strndup(arg, end);
    buffer->data[buffer->count + 1] = NULL;
    buffer->count++;
}
