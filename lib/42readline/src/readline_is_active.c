/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** readline_is_active
*/

#include <readline.h>
#include <readline/internal.h>


bool readline_is_active(void)
{
    return *rl_state_get();
}
