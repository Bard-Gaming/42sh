/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_cleanup
*/

#include <readline/terminal.h>


/*
** Restores the terminal to its
** original state.
*/
void rl_terminal_cleanup(void)
{
    terminal_t *terminal = rl_terminal_get();

    SEND_CODE(terminal, CURSOR_BLOCK);
    tcsetattr(terminal->fd, TCSANOW, &terminal->settings);
}
