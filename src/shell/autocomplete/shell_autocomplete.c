/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_autocomplete
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>


/*
** Retrieves the first match within the given
** match vector, then deletes the vector's data.
** The given vector may not be empty.
*/
static char *retrieve_best_match(sh_vector_t *vector)
{
    char *best_match;

    if (vector->count != 1) {
        sh_vector_delete(vector, NULL);
        return NULL;
    }
    best_match = sh_strjoin(vector->data[0], " ");
    sh_vector_delete(vector, NULL);
    return best_match;
}

/*
** 42sh's autocomplete function.
** This function will be passed onto
** the readline library.
*/
char *shell_autocomplete(const char *input)
{
    sh_data_t *data = sh_data_get();
    sh_vector_t matches;

    if (input == NULL || *input == '\0')
        return NULL;
    matches = shell_autocomplete_alias(input, data);
    if (matches.count != 0)
        return retrieve_best_match(&matches);
    matches = shell_autocomplete_path(input, data);
    if (matches.count != 0)
        return retrieve_best_match(&matches);
    return NULL;
}
