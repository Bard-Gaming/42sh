/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_next_word
*/

#include <readline/terminal.h>
#include <readline/internal.h>
#include <readline/buffer.h>


/*
** Moves the terminal to the next word.
** Nothing much to add, is there?..
*/
void rl_terminal_next_word(void)
{
    terminal_t *terminal = rl_terminal_get();
    string_buffer_t *buffer = rl_buffer_get();

    while (rl_is_word_char(buffer->data[terminal->cursor_index]))
        terminal->cursor_index++;
    while (!rl_is_word_char(buffer->data[terminal->cursor_index]))
        terminal->cursor_index++;
}
