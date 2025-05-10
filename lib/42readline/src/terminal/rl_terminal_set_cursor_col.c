/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_set_cursor_col
*/

#include <readline/terminal.h>
#include <stdio.h>


/*
** Sets the cursor position to the position
** specified by the second parameter.
**
** Technical Addendum:
** The size 16 is the maximum amount of characters
** that could make up the ANSI sequence.
** Furthermore, dprintf is not used, as the buffering
** it causes could break the display.
*/
void rl_terminal_set_cursor_col(int fd, int col)
{
    char code[16] = { 0 };

    snprintf(code, 16, "\033[%dG", col);
    SEND_CODE_FD(fd, code);
}
