/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_restore_canonical_mode
*/

#include <readline/internal.h>


/*
** Restores the default terminal mode
** for better printing.
*/
void rl_restore_canonical_mode(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}
