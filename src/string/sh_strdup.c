/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strdup
*/

#include <42sh/string.h>
#include <42sh/memory.h>
#include <string.h>


/*
** Duplicates a string into a new
** heap allocated buffer.
** This is the same as the C standard
** library's strdup() function, except
** that it uses shmalloc() instead of
** malloc().
** The returned pointer still needs to
** be passed to free() after use.
*/
char *sh_strdup(const char *restrict ref)
{
    size_t len = strlen(ref);
    char *duplicate = shmalloc((len + 1) * sizeof(char));

    return strcpy(duplicate, ref);
}
