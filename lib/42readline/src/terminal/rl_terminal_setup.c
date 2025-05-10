/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_setup
*/

#include <readline/terminal.h>


/*
** Disables canonical mode for the terminal
** whilst saving the previous terminal settings
** in the terminal (useful for restoring previous
** state after everything is done).
*/
static void disable_canonical_mode(terminal_t *terminal)
{
    struct termios non_canonical;

    tcgetattr(terminal->fd, &terminal->settings);
    non_canonical = terminal->settings;
    non_canonical.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(terminal->fd, TCSANOW, &non_canonical);
}

/*
** Sets up the terminal descriptor
** for use.
*/
void rl_terminal_setup(int fd)
{
    terminal_t *terminal = rl_terminal_get();
    cursor_pos_t pos;

    memset(terminal, 0, sizeof(terminal_t));
    terminal->fd = fd;
    disable_canonical_mode(terminal);
    pos = rl_terminal_get_cursor_pos(fd);
    terminal->start_col = pos.col >= 0 ? pos.col : 0;
    SEND_CODE(terminal, CURSOR_LINE);
}
