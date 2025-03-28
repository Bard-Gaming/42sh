/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_pipeline
*/

#include <42parser/parser.h>
#include <42parser/error.h>


ast_t *parse_pipeline(parser_t *parser, ast_t *atom)
{
    ast_t *result = ast_create(AT_PIPELINE);
    ast_program_t *nodes = ast_program_create();
    ast_t *current;

    result->data = nodes;
    ast_program_append(nodes, atom);
    while (parser->current->type == TT_PIPE) {
        parser_next(parser);
        current = parse_atom(parser);
        ast_program_append(nodes, current);
        if (current->type == AT_ERROR) {
            parser_errno_set(PE_NULL_COMMAND);
            return result;
        }
    }
    return result;
}
