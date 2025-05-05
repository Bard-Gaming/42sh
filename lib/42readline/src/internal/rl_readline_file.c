/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_readline_file
*/


#include <readline/internal.h>
#include <readline/buffer.h>


/*
** Readline function for an non-interactive
** (boring) file descriptor.
*/
char *rl_readline_file(int fd)
{
    ssize_t read_len;
    char input;

    rl_buffer_empty();
    read_len = read(fd, &input, 1);
    if (read_len <= 0)
        return NULL;
    while (read_len > 0) {
        rl_buffer_add_char(input);
        read_len = read(fd, &input, 1);
    }
    return rl_buffer_get_data();
}
