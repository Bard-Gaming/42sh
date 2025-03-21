/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_is_whitespace
*/

#include <42parser/lexer.h>
#include <stdbool.h>


/*
** Determines whether a given
** char is whitespace or not.
*/
bool lexer_is_whitespace(char c)
{
    return
        c == '\t' ||
        c == ' ';
}
