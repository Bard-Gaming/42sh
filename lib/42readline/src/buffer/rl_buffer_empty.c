/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_string_empty
*/

#include <readline/buffer.h>


/*
** Empty a given string buffer.
** This does not free the buffer, but
** merely renders it empty.
*/
void rl_buffer_empty(void)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (buffer->capacity == 0)
        return;
    buffer->data[0] = '\0';
    buffer->count = 0;
}
