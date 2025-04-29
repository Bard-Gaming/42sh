/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_scan
*/

#include <42parser/parser.h>


/*
** Scans the parser's current token type, and, if it
** matches, advances on to the next token (returning
** true). Otherwise, the parser is left unchanged and
** false is returned.
*/
bool parser_scan(parser_t *parser, token_type_t type)
{
    if (parser->current->type != type)
        return false;
    parser_next(parser);
    return true;
}
