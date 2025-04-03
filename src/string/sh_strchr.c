/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strchr
*/

#include <mysh/string.h>
#include <stdbool.h>


/*
** Returns a pointer to the first
** occurrence of <c> in the given
** <str>. If <c> is not in <str>,
** NULL is returned instead.
**
** Technical Addendum:
** This implementation of the strchr
** function doesn't take an int for
** <c>, since this is only in the C
** standard due to backwards compatibility,
** which doesn't apply here :)
*/
char *sh_strchr(const char *str, char c)
{
    if (str == NULL)
        return NULL;
    while (*str != '\0') {
        if (*str == c)
            return (void *)str;
        str++;
    }
    return NULL;
}
