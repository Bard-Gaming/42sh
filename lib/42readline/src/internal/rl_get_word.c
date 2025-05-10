/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_get_word_start
*/

#include <readline/internal.h>
#include <string.h>


/*
** Retrieves a pointer to the start
** of the word located at index in the
** given input.
*/
char *rl_get_word(const char *input, size_t index)
{
    const char *start = rl_get_word_start(input, index);
    const char *end = rl_get_word_end(start);

    return strndup(start, end - start);
}
