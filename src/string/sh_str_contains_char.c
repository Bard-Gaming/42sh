/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_str_contains_char
*/

#include <mysh/string.h>
#include <stdbool.h>


bool sh_str_contains_char(const char *str, char c)
{
    if (str == NULL)
        return false;
    while (*str != '\0') {
        if (*str == c)
            return true;
        str++;
    }
    return false;
}
