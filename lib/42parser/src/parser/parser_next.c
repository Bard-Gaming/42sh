/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_next
*/

#include <42parser/parser.h>
#include <42parser/lexer.h>


void parser_next(parser_t *parser)
{
    token_delete(parser->current);
    parser->current = parser->next;
    parser->next = lexer_scan();
}
