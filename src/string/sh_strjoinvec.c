/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_strjoinvec
*/

#include <42sh/string.h>
#include <42sh/memory.h>
#include <string.h>


/*
** Gets the aggregate length of every
** string within the argument vector.
*/
static size_t get_aggregate_length(const char **argv)
{
    size_t aggr_length = 0;

    while (*argv != NULL) {
        aggr_length += strlen(*argv);
        argv++;
    }
    return aggr_length;
}

/*
** Joins an argument vector together
** into a single, null-terminated string.
*/
char *sh_strjoinvec(const char **argv)
{
    size_t aggr_length = get_aggregate_length(argv);
    char *str = shmalloc((aggr_length + 1) * sizeof(char));
    char *current = str;

    while (*argv != NULL) {
        current = stpcpy(current, *argv);
        argv++;
    }
    return str;
}
