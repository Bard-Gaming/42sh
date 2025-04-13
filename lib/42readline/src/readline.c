/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline
*/

#include <readline.h>
#include <readline/buffer.h>
#include <readline/internal.h>
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

static char *error(void)
{
    *rl_state_get() = false;
    return NULL;
}

char *readline(int fd)
{
    ssize_t read_len;
    char input;

    rl_buffer_empty();
    *rl_state_get() = true;
    read_len = read(fd, &input, 1);
    if (read_len <= 0)
        return error();
    while (should_continue(fd, read_len, input)) {
        if (!rl_buffer_add_char(input))
            return error();
        read_len = read(fd, &input, 1);
    }
    *rl_state_get() = false;
    return rl_buffer_get_data();
}
