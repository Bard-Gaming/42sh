/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parser_term
*/

#include <42parser/parser.h>
#include <stdlib.h>


/*
** Delete all the data associated
** to the given parser.
*/
void parser_term(parser_t *parser)
{
    free(parser->current);
    free(parser->next);
    *parser = (parser_t){ NULL, NULL };
}
