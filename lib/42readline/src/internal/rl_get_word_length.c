/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_get_word_length
*/

#include <readline/internal.h>


/*
** Retrieves the length of the word
** located at the given index.
*/
size_t rl_get_word_length(const char *input, size_t index)
{
    const char *start = rl_get_word_start(input, index);
    const char *end = rl_get_word_end(input + index);

    return (size_t)(end - start);
}
