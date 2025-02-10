/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_strlen
*/

#include <mysh/string.h>


/*
** Returns the length of the given
** string of memory in bytes, up to
** a null value.
*/
size_t sh_strlen(const char *restrict str)
{
    size_t len;

    for (len = 0; str[len] != '\0'; len++);
    return len;
}
