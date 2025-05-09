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

static void move_history(int offset)
{
    string_buffer_t *buffer = rl_buffer_get();
    ssize_t new_index = buffer->history_index + offset;

    buffer->history_index = MAX(0, new_index);
    rl_buffer_set_history();
}

static void handle_arrow_key(char key)
{
    switch (key) {
    case 'A':
        return move_history(1);
    case 'B':
        return move_history(-1);
    case 'C':
        return move_index(1);
    case 'D':
        return move_index(-1);
    default:
        return rl_buffer_add_char(key);
    }
}

static void handle_arrows_delete(ssize_t *read_len, int fd)
{
    char input;

    (void)read_len;
    if (read(fd, &input, 1) != 1)
        return;
    if (input != '[')
        return rl_buffer_add_char(input);
    if (read(fd, &input, 1) != 1)
        return;
    handle_arrow_key(input);
}

static void handle_tab(void)
{
    string_buffer_t *buffer = rl_buffer_get();

    buffer->tabulation_count++;
    if (buffer->tabulation_count < AUTOCOMPLETE_LONG_CUTOFF)
        return rl_buffer_autocomplete();
    return rl_buffer_autocomplete_long();
}

/*
** Readline's control character handler.
** This function handles the given control
** character, updating the string buffer
** when necessary.
*/
void rl_handle_control_char(char c, ssize_t *read_len, int fd)
{
    switch (c) {
    case CHAR_DEL:
        return rl_buffer_rm_char();
    case '\x1b':
        return handle_arrows_delete(read_len, fd);
    case '\t':
        return handle_tab();
    default:
        return;
    }
}
