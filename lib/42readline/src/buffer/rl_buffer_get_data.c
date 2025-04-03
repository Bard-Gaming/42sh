/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_get_data
*/

#include <readline/buffer.h>


/*
** Returns a pointer to the data
** contained within the readline
** buffer. If the buffer doesn't
** contain any data, an empty
** string is returned, so not as
** to confused the return value
** with an error (in which case
** it would be NULL).
*/
char *rl_buffer_get_data(void)
{
    string_buffer_t *buffer = rl_buffer_get();

    return buffer->data == NULL ? "" : buffer->data;
}
