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
#include <stdio.h>
#include <string.h>

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
    char seq[2];

    if (*input == '\x1b') {
        if (read(fd, &seq[0], 1) == 1 && read(fd, &seq[1], 1) == 1) {
            if (seq[0] == '[' && (seq[1] == 'A' || seq[1] == 'B' || seq[1] == 'C' || seq[1] == 'D')) {
                *read_len = read(fd, input, 1);
                return 1;
            }
        }
        *read_len = read(fd, input, 1);
        return 1;
    }
    if (*input == '\t') {
        *read_len = read(fd, input, 1);
        return 1;
    }
    return 0;
}

static void print_buffer(int fd)
{
    string_buffer_t *buffer = rl_buffer_get();

    write(fd, "\33[2K\r", strlen("\33[2K\r"));
    if (buffer->data)
        write(fd, buffer->data, strlen(buffer->data));
}

/*
*Empty buffer
*store the first state of the line
*Disable canonical mode
*/
static setup_readline(struct termios *original)
{
    rl_buffer_empty();
    *rl_state_get() = true;
    disable_canonical_mode(original);
}

char *readline(int fd)
{
    ssize_t read_len;
    char input;
    struct termios original;

    setup_readline(&original);
    read_len = read(fd, &input, 1);
    if (read_len <= 0)
        return error();
    while (should_continue(fd, read_len, input)) {
        if (handle_special_chars(&input, &read_len, fd))
            continue;
        if (!rl_buffer_add_char(input))
            return error();
        print_buffer(fd);
        read_len = read(fd, &input, 1);
    }
    *rl_state_get() = false;
    restore_terminal_mode(&original);
    return rl_buffer_get_data();
}
