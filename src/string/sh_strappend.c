/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strappend
*/

#include <42sh/string.h>
#include <42sh/memory.h>
#include <string.h>


/*
** Appends the reference string to the destination,
** reallocating the destination buffer when necessary.
** Neither of the given pointers may be NULL.
*/
void sh_strappend(char **dest, const char *restrict ref)
{
    *dest = shreallocarray(
        *dest,
        strlen(*dest) + strlen(ref) + 1,
        sizeof(char)
    );
    strcat(*dest, ref);
}
