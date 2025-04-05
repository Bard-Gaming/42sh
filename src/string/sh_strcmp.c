/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strcmp
*/

#include <mysh/string.h>


/*
** Compares two strings.
** If both strings are identical, 0 is returned.
** Returns a position value if the first differing
** character of a is greater than the the first
** differing character of b, and a negative value
** if the first differing character of b is greater
** than the first differing character of a.
*/
int sh_strcmp(const char *a, const char *b)
{
    size_t i;

    for (i = 0; a[i] == b[i] && a[i] != '\0'; i++);
    return a[i] - b[i];
}
