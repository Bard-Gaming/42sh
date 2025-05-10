/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_add_char
*/

#include <readline/terminal.h>
#include <readline/buffer.h>


/*
** Inserts a character at the cursor's
** index.
*/
void rl_terminal_add_char(char c)
{
    terminal_t *terminal = rl_terminal_get();

    rl_buffer_insert_char(c, terminal->cursor_index);
    terminal->cursor_index++;
}
