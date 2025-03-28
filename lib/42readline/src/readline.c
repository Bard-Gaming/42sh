/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline
*/

#include <readline.h>
#include <readline/string.h>
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
    static string_buffer_t buffer = { 0 };
    ssize_t read_len;
    char input;

    rl_string_empty(&buffer);
    read_len = read(fd, &input, 1);
    if (read_len <= 0)
        return NULL;
    while (should_continue(fd, read_len, input)) {
        if (!rl_string_add_char(&buffer, input))
            return NULL;
        read_len = read(fd, &input, 1);
    }
    return buffer.data;
}
