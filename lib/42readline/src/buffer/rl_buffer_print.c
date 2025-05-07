/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_print
*/

#include <readline/buffer.h>
#include <string.h>
#include <unistd.h>


/*
** Clears the line displayed in the terminal
** and prints the current buffer.
** This function should be called after every
** buffer update.
*/
void rl_buffer_print(int fd)
{
    string_buffer_t *buffer = rl_buffer_get();
    size_t to_left;

    write(fd, CLEAR_LINE, strlen(CLEAR_LINE));
    write(fd, buffer->prompt, strlen(buffer->prompt));
    if (buffer->data)
        write(fd, buffer->data, buffer->count);
    if (buffer->count <= buffer->arrow_index)
        return;
    to_left = buffer->count - buffer->arrow_index;
    for (size_t i = 0; i < to_left; i++)
        write(fd, "\33[D", 3);
}
