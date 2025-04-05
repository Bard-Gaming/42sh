/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strjoin
*/

#include <mysh/string.h>


/*
** Creates a new string by joining
** two null-terminated strings together,
** in the order they were given.
** This new string must be freed.
*/
char *sh_strjoin(const char *restrict a, const char *restrict b)
{
    size_t a_len = sh_strlen(a);
    size_t b_len = sh_strlen(b);
    char *buffer = malloc((a_len + b_len + 1) * sizeof(char));

    for (size_t i = 0; i < a_len + b_len; i++)
        buffer[i] = i < a_len ? a[i] : b[i - a_len];
    buffer[a_len + b_len] = '\0';
    return buffer;
}
