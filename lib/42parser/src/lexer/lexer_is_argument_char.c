/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_is_argument_char
*/

#include <42parser/lexer.h>
#include <42parser/token.h>
#include <stdbool.h>


static const char *reserved_chars =
// Sidenote: The (infamous) Coding Style Checker
// expects me not to indent this for some reason.

" \t\n;"    // Whitespace / separators
"()<>&|"    // Operation chars
;


/*
** Determines whether or not
** a given char is a valid
** argument char or not.
*/
bool lexer_is_argument_char(char c)
{
    const char *current = reserved_chars;

    if (c == '\0')
        return false;
    while (*current != '\0') {
        if (c == *current)
            return false;
        current++;
    }
    return true;
}
