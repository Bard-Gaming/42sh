/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_line
*/

#include <42parser/parser.h>
#include <42parser/lexer.h>


ast_t *parse_line(const char *line)
{
    ast_t *result;
    parser_t parser;

    lexer_load_src(line);
    parser_init(&parser);
    result = parse_statement(&parser);
    parser_term(&parser);
    return result;
}
