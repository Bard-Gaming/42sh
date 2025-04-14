/*
** EPITECH PROJECT, 2025
** multishell
** File description:
** turn canonical mode to disable tabs and shit
*/

#include <readline.h>
#include <readline/buffer.h>
#include <readline/internal.h>
#include <unistd.h>
#include <stddef.h>
#include <termios.h>

/*
** Disable echo and canonical
** Remove tabulation and arrow indexes
*/
void disable_canonical_mode(struct termios *original)
{
    struct termios newSettings;

    tcgetattr(STDIN_FILENO, original);
    newSettings = *original;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);
}

/*
** Restore default terminal mode
** for better printing
*/
void restore_terminal_mode(struct termios *original)
{
    tcsetattr(STDIN_FILENO, TCSANOW, original);
}
