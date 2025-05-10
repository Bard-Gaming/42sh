/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_is_empty
*/

#include <readline/buffer.h>


/*
** Tells whether the buffer
** is empty or not.
*/
bool rl_buffer_is_empty(void)
{
    string_buffer_t *buffer = rl_buffer_get();

    return buffer->count == 0;
}
