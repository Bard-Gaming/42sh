/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_string_empty
*/

#include <readline/string.h>


/*
** Empty a given string buffer.
** This does not free the buffer, but
** merely renders it empty.
*/
void rl_string_empty(string_buffer_t *buffer)
{
    if (buffer->capacity == 0)
        return;
    buffer->data[0] = '\0';
    buffer->count = 0;
}
