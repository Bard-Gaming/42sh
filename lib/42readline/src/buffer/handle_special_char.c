/*
** EPITECH PROJECT, 2025
** multishell
** File description:
** handle_special_char
*/

#include <readline.h>
#include <readline/buffer.h>
#include <readline/internal.h>

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

static void check_value_after_esc(char *input, ssize_t *read_len,
    int fd, char seq[2])
{
    char temp;

    if (seq[0] == '[' && (seq[1] == 'C' || seq[1] == 'D'))
        move_index(seq[1] == 'C' ? 1 : -1);
    if (seq[0] == '[' && seq[1] == '3') {
        *read_len = read(fd, &temp, 1);
        if (temp == '~') {
            move_index(1);
            delete_char();
        }
    }
}

static int handle_arrows_delete(char *input, ssize_t *read_len, int fd)
{
    char seq[2];

    if (read(fd, &seq[0], 1) == 1 && read(fd, &seq[1], 1) == 1)
        check_value_after_esc(input, read_len, fd, seq);
        print_buffer(fd);
        *read_len = read(fd, input, 1);
        return 1;
}

int handle_special_chars(char *input, ssize_t *read_len, int fd)
{
    if (*input == 127) {
        delete_char();
        print_buffer(fd);
        *read_len = read(fd, input, 1);
        return 1;
    }
    if (*input == '\x1b') {
        handle_arrows_delete(input, read_len, fd);
        return 1;
    }
    if (*input == '\t') {
        *read_len = read(fd, input, 1);
        return 1;
    }
    return 0;
}
