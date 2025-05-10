/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_insert_char
*/

#include <readline/buffer.h>


/*
** Inserts a character at the given index.
** Does nothing if the index is out of bounds.
*/
void rl_buffer_insert_char(char c, size_t index)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (index > buffer->count)
        return;
    if (buffer->count + 1 >= buffer->capacity)
        rl_buffer_grow();
    for (size_t i = buffer->count; i > index; i--)
        buffer->data[i] = buffer->data[i - 1];
    buffer->data[index] = c;
    buffer->count++;
    buffer->data[buffer->count] = '\0';
}
