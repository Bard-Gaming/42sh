/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_autocomplete
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <string.h>


/*
** Determines whether or not the given
** char is common to all matches within
** the vector.
*/
static bool has_extra_char(const sh_vector_t *vector, char extra, size_t index)
{
    const char *current;

    for (size_t i = 0; i < vector->count; i++) {
        current = vector->data[i];
        if (current[index] != extra)
            return false;
    }
    return true;
}

/*
** Yields the result with the most common
** characters.
*/
static char *get_common_prefix(const sh_vector_t *vector, size_t input_len)
{
    char extra_char = ((const char *)vector->data[0])[input_len];
    size_t common_len = input_len;

    while (extra_char != '\0') {
        if (!has_extra_char(vector, extra_char, common_len))
            return strndup(vector->data[0], common_len);
        common_len++;
        extra_char = ((const char *)vector->data[0])[common_len];
    }
    return strndup(vector->data[0], common_len);
}

/*
** Retrieves the best match within the given
** match vector, then deletes the vector's data.
** The given vector may not be empty.
*/
static char *retrieve_best_match(sh_vector_t *vector, const char *input)
{
    char *best_match = vector->count == 1 ?
        sh_strjoin(vector->data[0], " ") :
        get_common_prefix(vector, strlen(input));

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
    sh_vector_t temp;

    if (input == NULL || *input == '\0')
        return NULL;
    matches = shell_autocomplete_alias(input, data);
    temp = shell_autocomplete_path(input, data);
    sh_vector_move_unique(&matches, &temp);
    if (matches.count != 0)
        return retrieve_best_match(&matches, input);
    return NULL;
}
