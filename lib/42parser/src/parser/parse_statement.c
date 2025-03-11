/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_statement
*/

#include <42parser/parser.h>


ast_t *parse_statement(parser_t *parser)
{
    return parse_binary_operation(parser);
}
