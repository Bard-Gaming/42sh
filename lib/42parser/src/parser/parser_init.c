/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_init
*/

#include <42parser/parser.h>
#include <42parser/lexer.h>


/*
** Initialize a parser.
*/
void parser_init(parser_t *parser)
{
    parser->current = lexer_scan();
    parser->next = lexer_scan();
}
