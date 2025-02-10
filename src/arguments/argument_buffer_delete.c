/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** argument_buffer_delete
*/

#include <mysh/arguments.h>


/*
** Delete the argument buffer and
** all of its containing data
*/
void argument_buffer_delete(argument_buffer_t *buffer)
{
    for (size_t i = 0; i < buffer->count; i++)
        free(buffer->data[i]);
    free(buffer->data);
    free(buffer);
}
