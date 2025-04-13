/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_state_get
*/

#include <readline/internal.h>


/*
** Gets a pointer that stores the
** current state of the readline library.
*/
bool *rl_state_get(void)
{
    static bool state = false;

    return &state;
}
