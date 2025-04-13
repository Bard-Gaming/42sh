/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_pipeline
*/

#include <42parser/parser.h>
#include <42parser/error.h>


static ast_t *create_pipeline(parser_t *parser, ast_t *atom)
{
    ast_t *result = ast_create(AT_PIPELINE);
    ast_node_buffer_t *nodes = ast_node_buffer_create();
    ast_t *current;

    result->data = nodes;
    ast_node_buffer_append(nodes, atom);
    while (parser->current->type == TT_PIPE) {
        parser_next(parser);
        current = parse_atom(parser);
        ast_node_buffer_append(nodes, current);
        if (current->type == AT_ERROR) {
            parser_errno_set(PE_NULL_COMMAND);
            return result;
        }
    }
    return result;
}

/*
** Parses a pipeline.
** If no pipes follow the first atom
** (i.e. this isn't a pipeline), the
** atom is returned without getting
** modified.
*/
ast_t *parse_pipeline(parser_t *parser)
{
    ast_t *atom = parse_atom(parser);

    if (parser->current->type == TT_PIPE)
        atom = create_pipeline(parser, atom);
    return atom;
}
