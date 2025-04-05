/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strlen
*/

#include <mysh/string.h>


/*
** Returns the length of the given
** string of memory in bytes, up to
** the string's null-terminating byte.
*/
size_t sh_strlen(const char *restrict str)
{
    size_t len;

    for (len = 0; str[len] != '\0'; len++);
    return len;
}
