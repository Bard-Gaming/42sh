/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** argument_buffer_create
*/

#include <mysh/arguments.h>

/*
** Create an argument buffer
** with initial capacity
*/
argument_buffer_t *argument_buffer_create(void)
{
    argument_buffer_t *buffer = malloc(sizeof(argument_buffer_t));

    buffer->data = malloc(SH_AB_INITIAL_CAPACITY * sizeof(char *));
    buffer->capacity = SH_AB_INITIAL_CAPACITY;
    buffer->count = 0;
    return buffer;
}
