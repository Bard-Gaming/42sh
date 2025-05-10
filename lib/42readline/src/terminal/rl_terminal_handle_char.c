/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_handle_char
*/

#include <readline/terminal.h>
#include <readline/internal.h>
#include <readline/buffer.h>


/*
** Handles the given character
*/
void rl_terminal_handle_char(char c)
{
    terminal_t *terminal = rl_terminal_get();

    if (c != '\t')
        terminal->tab_count = 0;
    if (rl_is_control_char(c))
        rl_terminal_handle_control_char(c);
    else
        rl_terminal_add_char(c);
}
