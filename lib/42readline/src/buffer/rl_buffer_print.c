/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_buffer_print
*/

#include <readline/buffer.h>
#include <unistd.h>


/*
** Writes the buffer's content to
** the given file descriptor.
*/
void rl_buffer_print(int fd)
{
    string_buffer_t *buffer = rl_buffer_get();

    (void)!write(fd, buffer->data, buffer->count);
}
