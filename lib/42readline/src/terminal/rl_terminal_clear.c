/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_clear
*/

#include <readline/terminal.h>
#include <readline/buffer.h>


/*
** Resets the terminal's buffer to
** its starting state.
*/
void rl_terminal_clear(void)
{
    terminal_t *terminal = rl_terminal_get();

    terminal->cursor_index = 0;
    terminal->tab_count = 0;
    rl_buffer_empty();
}
