/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_add_char
*/

#include <readline/buffer.h>


/*
** Adds a char to the string buffer,
** increasing its size when needed.
*/
void rl_buffer_add_char(char c)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (buffer->count + 1 >= buffer->capacity)
        rl_buffer_grow();
    buffer->data[buffer->count] = c;
    buffer->count++;
    buffer->data[buffer->count] = '\0';
}
