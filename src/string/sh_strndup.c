/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strndup
*/

#include <mysh/string.h>


/*
** Duplicate a string into heap
** memory.
*/
char *sh_strndup(const char *restrict str, size_t end)
{
    char *duplicate;
    size_t i = 0;

    if (end == 0)
        return NULL;
    duplicate = malloc((end + 1) * sizeof(char));
    for (; str[i] != '\0' && i < end; i++)
        duplicate[i] = str[i];
    for (; i < end; i++)
        duplicate[i] = '\0';
    duplicate[end] = '\0';
    return duplicate;
}
