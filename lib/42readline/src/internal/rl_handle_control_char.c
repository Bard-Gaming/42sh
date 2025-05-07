/*
** EPITECH PROJECT, 2025
** multishell
** File description:
** handle_special_char
*/

#include <readline/internal.h>
#include <readline/buffer.h>


static void move_index(int offset)
{
    string_buffer_t *buffer = rl_buffer_get();
    ssize_t new_index = buffer->arrow_index + offset;

    buffer->arrow_index = CLAMP(0, new_index, buffer->count);
}

static void check_value_after_esc(ssize_t *read_len, int fd, char seq[2])
{
    char temp;

    if (seq[0] == '[' && (seq[1] == 'C' || seq[1] == 'D'))
        move_index(seq[1] == 'C' ? 1 : -1);
    if (!(seq[0] == '[' && seq[1] == '3'))
        return;
    *read_len = read(fd, &temp, 1);
    if (*read_len == 1 && temp != '~')
        return rl_buffer_add_char(temp);
    move_index(1);
    rl_buffer_rm_char();
}

static void handle_arrows_delete(char *input, ssize_t *read_len, int fd)
{
    char seq[2];

    if (read(fd, seq, 1) == 1 && read(fd, seq +1, 1) == 1)
        check_value_after_esc(read_len, fd, seq);
}

/*
** Readline's control character handler.
** This function handles the given control
** character, updating the string buffer
** when necessary.
**
** TODO: Implement tabs ('\t')
*/
void rl_handle_control_char(char *input, ssize_t *read_len, int fd)
{
    switch (*input) {
    case CHAR_DEL:
        return rl_buffer_rm_char();
    case '\x1b':
        return handle_arrows_delete(input, read_len, fd);
    case '\t':
        return;
    default:
        return;
    }
}
