/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_rm_char
*/

#include <readline/buffer.h>


/*
** Removes the char located right before
** the arrow index. If the arrow index is
** at 0 (i.e. no chars can be removed),
** this function does nothing.
*/
void rl_buffer_rm_char(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t rm_index = buffer->arrow_index - 1;

    if (buffer->count == 0 || buffer->arrow_index == 0)
        return;
    for (size_t i = rm_index; i < buffer->count; i++)
        buffer->data[i] = buffer->data[i + 1];
    buffer->arrow_index--;
    buffer->count--;
}
