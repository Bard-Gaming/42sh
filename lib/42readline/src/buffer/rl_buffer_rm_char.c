/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_rm_char
*/

#include <readline/buffer.h>


/*
** Removes the character located at the
** given index. If the given index is
** out of bounds, this function does
** nothing.
*/
void rl_buffer_rm_char(size_t index)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (index >= buffer->count)
        return;
    for (size_t i = index; i < buffer->count; i++)
        buffer->data[i] = buffer->data[i + 1];
    buffer->count--;
}
