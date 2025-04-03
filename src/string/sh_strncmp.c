/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strncmp
*/

#include <mysh/string.h>


int sh_strncmp(const char *restrict a, const char *restrict b, size_t n)
{
    size_t i;

    for (i = 0; a[i] == b[i] && a[i] != '\0' && i < n - 1; i++);
    return a[i] - b[i];
}
