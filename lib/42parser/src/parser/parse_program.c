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


/*
** Parse a program into an AST.
** The program node ends without errors
** when it reaches the token identified
** by the "end" parameter.
*/
ast_t *parse_program(parser_t *parser, token_type_t end)
{
    ast_t *node = ast_create(AT_PROGRAM);
    ast_program_t *prog = ast_program_create();
    ast_t *current_stmt;

    node->data = prog;
    do {
        while (parser->current->type == TT_SEPARATOR)
            parser_next(parser);
        if (parser->current->type == end)
            break;
        current_stmt = parse_statement(parser);
        ast_program_append(prog, current_stmt);
    } while (parser->current->type == TT_SEPARATOR);
    return node;
}
