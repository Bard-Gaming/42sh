/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_strcpy
*/

#include <mysh/string.h>


char *sh_strcpy(char *dest, const char *ref)
{
    size_t i;

    for (i = 0; ref[i] != '\0'; i++)
        dest[i] = ref[i];
    dest[i] = '\0';
    return dest + i;
}
