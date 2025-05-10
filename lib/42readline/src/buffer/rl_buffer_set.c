/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_set
*/

#include <readline/buffer.h>
#include <string.h>


/*
** Sets the buffer to the given source
** string.
*/
void rl_buffer_set(const char *src)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t src_len = strlen(src);

    while (src_len + 1 >= buffer->capacity)
        rl_buffer_grow();
    memcpy(buffer->data, src, src_len + 1);
    buffer->count = src_len;
}
