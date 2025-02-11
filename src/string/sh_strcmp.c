/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_strcmp
*/

#include <mysh/string.h>


int sh_strcmp(const char *restrict a, const char *restrict b)
{
    size_t i;

    for (i = 0; a[i] == b[i] && a[i] != '\0'; i++);
    return a[i] - b[i];
}
