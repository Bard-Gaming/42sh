/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_prev_word
*/

#include <readline/terminal.h>
#include <readline/internal.h>
#include <readline/buffer.h>


static bool is_word_char(string_buffer_t *buffer, terminal_t *terminal)
{
    return rl_is_word_char(
        buffer->data[terminal->cursor_index]
    );
}

/*
** Moves the terminal cursor to the previous word.
** Nothing much to add, is there?..
*/
void rl_terminal_prev_word(void)
{
    terminal_t *terminal = rl_terminal_get();
    string_buffer_t *buffer = rl_buffer_get();

    if (terminal->cursor_index == 0)
        return;
    terminal->cursor_index--;
    while (terminal->cursor_index != 0 && is_word_char(buffer, terminal))
        terminal->cursor_index--;
    while (terminal->cursor_index != 0 && !is_word_char(buffer, terminal))
        terminal->cursor_index--;
    terminal->cursor_index += terminal->cursor_index != 0;
}
