/*
** EPITECH PROJECT, 2025
** multishell
** File description:
** handle_special_char
*/

#include <readline/internal.h>
#include <readline/buffer.h>


static void move_index(int move)
{
    string_buffer_t *buffer = rl_buffer_get();
    ssize_t new = buffer->arrow_index + move;

    buffer->arrow_index = CLAMP(0, new, buffer->count);
}

static void check_value_after_esc(ssize_t *read_len, int fd, char seq[2])
{
    char temp;

    if (seq[0] == '[' && (seq[1] == 'C' || seq[1] == 'D'))
        move_index(seq[1] == 'C' ? 1 : -1);
    if (!(seq[0] == '[' && seq[1] == '3'))
        return;
    *read_len = read(fd, &temp, 1);
    if (temp != '~')
        return;
    move_index(1);
    rl_buffer_rm_char();
}

static void handle_arrows_delete(char *input, ssize_t *read_len, int fd)
{
    char seq[2];

    if (read(fd, &seq[0], 1) == 1 && read(fd, &seq[1], 1) == 1)
        check_value_after_esc(read_len, fd, seq);
    rl_buffer_print(fd);
    *read_len = read(fd, input, 1);
}

/*
** Handles control chars.
** Returns true if the given char has been
** handled, and false if not.
** Do note that an unhandled char doesn't mean
** an error, as it usually means the given
** character is not a control char.
*/
bool rl_handle_control_chars(char *input, ssize_t *read_len, int fd)
{
    switch (*input) {
    case CHAR_DEL:
        rl_buffer_rm_char();
        rl_buffer_print(fd);
        *read_len = read(fd, input, 1);
        return true;
    case '\x1b':
        handle_arrows_delete(input, read_len, fd);
        return true;
    case '\t':
        *read_len = read(fd, input, 1);
        return true;
    default:
        return false;
    }
}
