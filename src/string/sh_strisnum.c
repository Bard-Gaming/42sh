/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strisnum
*/

#include <42sh/string.h>


/*
** Tells whether or not a given string
** is a (positive) number or not.
*/
bool sh_isnum(const char *repr)
{
    while (*repr != '\0') {
        if (!('0' <= *repr && *repr <= '9'))
            return false;
        repr++;
    }
    return true;
}
