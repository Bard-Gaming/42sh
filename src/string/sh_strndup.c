/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strndup
*/

#include <mysh/string.h>


/*
** Functions the same as sh_strdup,
** with the difference that this function
** stops after n bytes.
** The newly allocated buffer will always
** be of size n + 1, and all bytes that exceed
** the given reference string will be set to
** null.
*/
char *sh_strndup(const char *restrict str, size_t n)
{
    char *duplicate;
    size_t i = 0;

    if (n == 0)
        return NULL;
    duplicate = malloc((n + 1) * sizeof(char));
    for (; str[i] != '\0' && i < n; i++)
        duplicate[i] = str[i];
    for (; i < n; i++)
        duplicate[i] = '\0';
    duplicate[n] = '\0';
    return duplicate;
}
