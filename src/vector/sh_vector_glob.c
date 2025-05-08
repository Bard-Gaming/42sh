/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_vector_glob
*/

#include <42sh/vector.h>
#include <42sh/string.h>
#include <stdlib.h>


/*
** Applies globbing to all elements of the
** given vector. This assumes the given vector
** is a vector of strings, and may not be called
** with a vector containing any amount of
** non-strings.
** This does nothing if the given argument vector
** is empty.
*/
void sh_vector_glob(sh_vector_t *argv, bool sanitize)
{
    char *globbed_result;

    for (size_t i = 0; i < argv->count; i++) {
        globbed_result = sh_strglob(argv->data[i], sanitize);
        free(argv->data[i]);
        argv->data[i] = globbed_result;
    }
}
