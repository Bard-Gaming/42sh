/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_autocomplete_long
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <stdlib.h>


/*
** Prints all matches found for the autocompletion
** of the given input.
*/
void shell_autocomplete_long(const char *input)
{
    sh_data_t *data = sh_data_get();
    sh_vector_t matches = { 0 };
    sh_vector_t temp_matches;

    matches = shell_autocomplete_alias(input, data);
    temp_matches = shell_autocomplete_path(input, data);
    sh_vector_append_range(&matches, &temp_matches);
    sh_vector_delete(&temp_matches, NULL);
    sh_print_columns((char **)matches.data);
    sh_vector_delete(&matches, NULL);
}
