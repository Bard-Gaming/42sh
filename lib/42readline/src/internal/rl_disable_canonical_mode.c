/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_disable_canonical_mode
*/

#include <readline/internal.h>


/*
** Disable echo and canonical mode for fd.
** Removes tabulation and arrow indexes.
*/
void rl_disable_canonical_mode(int fd, struct termios *original)
{
    struct termios newSettings;

    tcgetattr(fd, original);
    newSettings = *original;
    newSettings.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(fd, TCSANOW, &newSettings);
}
