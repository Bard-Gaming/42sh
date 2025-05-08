/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_autocomplete_alias
*/

#include <42sh/shell.h>
#include <42sh/symbols.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <string.h>
#include <stdlib.h>


/*
** Finds all alias names that start
** with the given input, and returns
** a vector containing all matches.
** The resulting vector should be passed
** to sh_vector_delete after use.
*/
sh_vector_t shell_autocomplete_alias(const char *input, const sh_data_t *data)
{
    size_t prefix_len = strlen(input);
    sh_vector_t matches = { 0 };
    const char *alias_name;

    for (size_t i = 0; i < data->aliases->capacity; i++) {
        alias_name = data->aliases->data[i].name;
        if (alias_name == NULL)
            continue;
        if (strncmp(alias_name, input, prefix_len) != 0)
            continue;
        sh_vector_push_back(&matches, sh_strdup(alias_name));
    }
    return matches;
}
