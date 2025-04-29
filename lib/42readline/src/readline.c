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

/*
*Clear the line and print buffer
*Update after each character
*/
static void print_buffer(int fd)
{
    string_buffer_t *buffer = rl_buffer_get();
    const char *CLEAR_LINE = "\33[2K\r";
    int len;
    int to_left;

    write(fd, CLEAR_LINE, strlen(CLEAR_LINE));
    if (buffer->data)
        write(fd, buffer->data, strlen(buffer->data));
    if (buffer->arrow_index < (int)strlen(buffer->data)) {
        len = strlen(buffer->data);
        to_left = len - buffer->arrow_index;
        for (int i = 0; i < to_left; i++)
            write(fd, "\33[D", 3);
    }
}

static bool should_continue(int fd, ssize_t read_len, char c)
{
    if (read_len < 0)
        return false;
    if (isatty(fd) && c == '\n')
        return false;
    if (read_len != 0) {
        return true;
    }
    return false;
}

static char *error(void)
{
    *rl_state_get() = false;
    return NULL;
}

static void delete_char(void)
{
    string_buffer_t *buffer = rl_buffer_get();
    int len = 0;

    if (buffer->data)
        len = strlen(buffer->data);
    if (buffer->arrow_index == 0) {
        return;
    } else {
        cut_buffer();
    }
    buffer->arrow_index--;
    buffer->count--;
}

static void move_index(int move)
{
    string_buffer_t *buffer = rl_buffer_get();

    if (buffer->arrow_index == 0)
        return;
    buffer->arrow_index += move;
}

static void move_arrows(char seq[2])
{
    if (seq[0] == '[')
        move_index(seq[1] == 'C' ? 1 : -1);
}

static int handle_special_chars(char *input, ssize_t *read_len, int fd)
{
    char seq[2];

    if (*input == 127) {
        delete_char();
        print_buffer(fd);
        *read_len = read(fd, input, 1);
        return 1;
    }
    if (*input == '\x1b') {
        if (read(fd, &seq[0], 1) == 1 && read(fd, &seq[1], 1) == 1)
            move_arrows(seq);
        print_buffer(fd);
        *read_len = read(fd, input, 1);
        return 1;
    }
    if (*input == '\t') {
        *read_len = read(fd, input, 1);
        return 1;
    }
    return 0;
}

/*
*Empty buffer
*store the first state of the line
*Disable canonical mode
*/
static void setup_readline(struct termios *original)
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
