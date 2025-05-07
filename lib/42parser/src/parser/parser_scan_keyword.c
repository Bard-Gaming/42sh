/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_scan_keyword
*/

#include <42parser/parser.h>


/*
** Scans the parser's current token type to match a
** given keyword. If the keyword is matched, the parser
** moves on to the next token and returns true.
** Otherwise, false is returned and the parser stays
** on the errenous token.
*/
bool parser_scan_keyword(parser_t *parser, const char *keyword)
{
    if (!token_match(parser->current, keyword))
        return false;
    parser_next(parser);
    return true;
}
