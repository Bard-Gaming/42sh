/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** lexer_make_error
*/

#include <42parser/lexer.h>
#include <42parser/token.h>
#include <42parser/error.h>


token_t *lexer_make_error(parser_errno_t error)
{
    parser_errno_set(error);
    return token_create(TT_ERROR, NULL, 0);
}
