/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_strcpy
*/

#include <mysh/string.h>


void sh_strcpy(char *dest, const char *ref)
{
    for (size_t i = 0; ref[i] != '\0'; i++)
        dest[i] = ref[i];
}
