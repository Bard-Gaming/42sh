/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_program
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/token.h>
#include <42parser/error.h>


/*
** Sets the appropriate error message
** depending on the ending token.
*/
static void set_error(parser_t *parser)
{
    if (P_ERRNO != PE_NONE)
        return;
    switch (parser->current->type) {
    case TT_RPAREN:
        return parser_errno_set(PE_UNMATCHED_RPAREN);
    default:
        return parser_errno_set(PE_WRONG_SYNTAX);
    }
}

/*
** Parse a program into an AST.
** The program node ends without errors
** when it reaches the EOF token.
*/
ast_t *parse_program(parser_t *parser)
{
    ast_t *node = ast_create(AT_PROGRAM);
    ast_node_buffer_t *prog = ast_node_buffer_create();
    ast_t *current_stmt;

    node->data = prog;
    do {
        while (parser->current->type == TT_SEPARATOR)
            parser_next(parser);
        if (parser->current->type == TT_EOF)
            break;
        current_stmt = parse_statement(parser);
        ast_node_buffer_append(prog, current_stmt);
        if (current_stmt->type == AT_ERROR)
            return node;
    } while (parser->current->type == TT_SEPARATOR);
    if (parser->current->type != TT_EOF)
        set_error(parser);
    return node;
}
