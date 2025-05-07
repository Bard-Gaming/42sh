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
static size_t get_aggregate_length(const char **argv, const char *sep)
{
    size_t aggr_length = 0;
    size_t sep_len = strlen(sep);

    while (*argv != NULL) {
        aggr_length += strlen(*argv) + sep_len;
        argv++;
    }
    return aggr_length - sep_len;
}

/*
** Joins an argument vector together
** into a single, null-terminated string.
** The arguments will be separated by <sep>.
*/
char *sh_strjoinvec(const char **argv, const char *sep)
{
    size_t aggr_length = get_aggregate_length(argv, sep);
    char *str = shmalloc((aggr_length + 1) * sizeof(char));
    char *current = str;

    if (*argv != NULL) {
        current = stpcpy(current, *argv);
        argv++;
    }
    while (*argv != NULL) {
        current = stpcpy(current, sep);
        current = stpcpy(current, *argv);
        argv++;
    }
    return str;
}
