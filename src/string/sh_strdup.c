/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strdup
*/

#include <mysh/string.h>


/*
** Duplicates a string into a newly
** allocated buffer.
** Functionally the same as calling
** malloc and strcpy.
** The returned string must be freed
** by the user.
*/
char *sh_strdup(const char *restrict str)
{
    char *duplicate;
    size_t str_len = sh_strlen(str);

    duplicate = malloc((str_len + 1) * sizeof(char));
    for (size_t i = 0; i < str_len; i++)
        duplicate[i] = str[i];
    duplicate[str_len] = '\0';
    return duplicate;
}
