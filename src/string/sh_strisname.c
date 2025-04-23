/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strisname
*/

#include <42sh/string.h>
#include <stdio.h>


/*
** Determines wether or not a given
** character is valid within a variable
** name.
*/
static bool is_name_char(char c)
{
    return
        ('a' <= c && c <= 'z') ||
        ('A' <= c && c <= 'Z') ||
        ('0' <= c && c <= '9') ||
        (c == '_');
}

/*
** Error to return when the first character
** is numeric.
*/
static bool invalid_start(const char *restrict prefix)
{
    fprintf(
        stderr,
        "%s: Variable name must begin with a letter.\n",
        prefix
    );
    return false;
}

/*
** Error to return when an illegal variable name
** character was used.
*/
static bool illegal_char(const char *restrict prefix)
{
    fprintf(
        stderr,
        "%s: Variable name must contain alphanumeric characters.\n",
        prefix
    );
    return false;
}

/*
** Determines whether or not a given string is
** a valid variable name or not.
** Valid variable names are composed entirely of
** alphanumeric characters, as well as '_'.
** This first char may not be numeric.
*/
bool sh_strisname(const char *restrict str, const char *restrict prefix)
{
    if ('0' <= *str && *str <= '9')
        return invalid_start(prefix);
    str++;
    while (*str != '\0') {
        if (!is_name_char(*str))
            return illegal_char(prefix);
        str++;
    }
    return true;
}
