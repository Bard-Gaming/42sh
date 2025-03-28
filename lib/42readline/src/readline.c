/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline
*/

#include <readline.h>
#include <readline/buffer.h>
#include <unistd.h>
#include <stddef.h>


static bool should_continue(int fd, ssize_t read_len, char c)
{
    if (read_len < 0)
        return false;
    if (isatty(fd) && c == '\n')
        return false;
    return read_len != 0;
}

char *readline(int fd)
{
    ssize_t read_len;
    char input;

    rl_buffer_empty();
    read_len = read(fd, &input, 1);
    if (read_len <= 0)
        return NULL;
    while (should_continue(fd, read_len, input)) {
        if (!rl_buffer_add_char(input))
            return NULL;
        read_len = read(fd, &input, 1);
    }
    return rl_buffer_get()->data;
}
