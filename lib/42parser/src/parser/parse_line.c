/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_line
*/

#include <42parser/parser.h>
#include <42parser/lexer.h>


/*
** Parses a line into an abstract syntax
** tree.
**
** Returns NULL if a syntax error was caught
** or if the input didn't contain any tokens.
**
** To determine whether or not an error has
** occurred or not, please use P_ERRNO.
**
** The given ast should be deleted with
** ast_delete once it isn't needed anymore.
*/
ast_t *parse_line(const char *line)
{
    ast_t *result;
    parser_t parser;

    parser_errno_set(PE_NONE);
    lexer_load_src(line);
    parser_init(&parser);
    result = parse_statement(&parser);
    parser_term(&parser);
    if (P_ERRNO == 0)
        return result;
    ast_delete(result);
    return NULL;
}
