/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_is_argument
*/

#include <42parser/lexer.h>
#include <stdbool.h>


static bool is_alphanumeric(char c)
{
    return
        ('a' <= c && c <= 'z') ||
        ('A' <= c && c <= 'Z') ||
        ('0' <= c && c <= '9');
}

/*
** Determines whether or not
** a given char is a valid
** argument char or not.
*/
bool lexer_is_argument(char c)
{
    const char *current = ARGUMENT_NON_ALPHA_NUM_CHARS;

    if (is_alphanumeric(c))
        return true;
    while (*current != '\0') {
        if (c == *current)
            return true;
        current++;
    }
    return false;
}
