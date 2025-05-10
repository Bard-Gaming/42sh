/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_refresh
*/

#include <readline/terminal.h>
#include <readline/buffer.h>


/*
** Yields the count of characters stored
** inside of the string buffer.
*/
static size_t get_buffer_count(void)
{
    string_buffer_t *buffer = rl_buffer_get();

    return buffer->count;
}

/*
** Refreshes the terminal, displaying the
** buffer anew.
*/
void rl_terminal_refresh(void)
{
    terminal_t *terminal = rl_terminal_get();

    rl_terminal_set_cursor_col(terminal->fd, terminal->start_col);
    SEND_CODE(terminal, CLEAR_LINE);
    rl_buffer_print(terminal->fd);
    for (size_t i = get_buffer_count(); i > terminal->cursor_index; i--)
        SEND_CODE(terminal, CURSOR_LEFT);
}
