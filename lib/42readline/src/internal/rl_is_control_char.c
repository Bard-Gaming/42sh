/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_is_control_char
*/

#include <readline/internal.h>


/*
** Returns true if the given character
** is a control char, and false if not.
*/
bool rl_is_control_char(char c)
{
    return
        c <= CONTROL_CHAR_MAX ||
        c == CHAR_DEL;
}
