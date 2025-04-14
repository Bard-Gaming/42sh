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
#include <termios.h>

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

static int handle_special_chars(char *input, ssize_t *read_len, int fd)
{
    if (*input == '\t') {
        *read_len = read(fd, input, 1);
        return 1;
    }
    return 0;
}

char *readline(int fd)
{
    ssize_t read_len;
    char input;
    struct termios original;

    rl_buffer_empty();
    *rl_state_get() = true;
    disable_canonical_mode(&original);
    read_len = read(fd, &input, 1);
    if (read_len <= 0)
        return error();
    while (should_continue(fd, read_len, input)) {
        if (handle_special_chars(&input, &read_len, fd))
            continue;
        if (!rl_buffer_add_char(input))
            return error();
        read_len = read(fd, &input, 1);
    }
    *rl_state_get() = false;
    restore_terminal_mode(&original);
    return rl_buffer_get_data();
}
