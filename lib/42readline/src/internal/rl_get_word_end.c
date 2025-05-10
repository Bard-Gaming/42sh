/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_get_word_end
*/

#include <readline/internal.h>


/*
** Retrieves a pointer to the end of the
** word in the input buffer.
*/
char *rl_get_word_end(const char *input)
{
    while (rl_is_word_char(*input))
        input++;
    return (char *)input;
}
