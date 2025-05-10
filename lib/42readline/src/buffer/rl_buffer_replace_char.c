/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_replace_char
*/

#include <readline/buffer.h>


/*
** Replaces the character at the given
** index to the given character.
** If the index is out of bounds, this
** does nothing.
*/
void rl_buffer_replace_char(char c, size_t index)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (index >= buffer->count)
        return;
    buffer->data[index] = c;
}
