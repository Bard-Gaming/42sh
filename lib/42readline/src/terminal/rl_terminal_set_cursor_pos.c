/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_set_cursor_pos
*/

#include <readline/terminal.h>
#include <stdio.h>


/*
** Sets the cursor position to the position
** specified by the second parameter.
**
** Technical Addendum:
** The size 32 is the maximum amount of characters
** that could make up the ANSI sequence.
*/
void rl_terminal_set_cursor_pos(int fd, cursor_pos_t pos)
{
    char code[32] = { 0 };

    snprintf(code, 32, "\033[%d;%dH", pos.row, pos.col);
    SEND_CODE_FD(fd, code);
}
