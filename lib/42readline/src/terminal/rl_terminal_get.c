/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_terminal_get
*/

#include <readline/terminal.h>


/*
** Retrieves a pointer to the library's
** terminal descriptor.
*/
terminal_t *rl_terminal_get(void)
{
    static terminal_t terminal;

    return &terminal;
}
