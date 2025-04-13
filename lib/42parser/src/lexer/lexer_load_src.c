/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_load_src
*/

#include <42parser/lexer.h>


/*
** Loads the given lexer with a given
** input (src). This can't fail, so
** no return is needed.
*/
void lexer_load_src(lexer_t *lexer, const char *src)
{
    lexer->start = src;
    lexer->current = src;
}
