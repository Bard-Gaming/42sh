/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strcpy
*/

#include <mysh/string.h>


/*
** Copies all characters (null-terminating byte included)
** from the reference to the destination, and returns
** a pointer to the destination's null-terminating byte.
*/
char *sh_strcpy(char *dest, const char *ref)
{
    size_t i;

    for (i = 0; ref[i] != '\0'; i++)
        dest[i] = ref[i];
    dest[i] = '\0';
    return dest + i;
}
