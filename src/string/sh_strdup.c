/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** sh_strdup
*/

#include <mysh/string.h>


/*
** Duplicate a string into heap
** memory.
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
