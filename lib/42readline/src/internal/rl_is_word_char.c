/*
** EPITECH PROJECT, 2025
** Project - 42readline
** File description:
** Implementation for
** rl_is_word_char
*/

#include <readline/internal.h>


static const char word_chars[] = {
    ' ', '\t', '\n', ';',
    '(', ')', '<', '>',
    '&', '|', '\'', '"',

    '\0',  // keep last
};


/*
** Tells whether or not the given character
** is a word character.
*/
bool rl_is_word_char(char c)
{
    const char *current = word_chars;

    while (*current != '\0') {
        if (*current == c)
            return false;
        current++;
    }
    return true;
}
