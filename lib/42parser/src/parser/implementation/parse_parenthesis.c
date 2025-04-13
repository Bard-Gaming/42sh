/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_parenthesis
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/error.h>
#include <stdbool.h>


/*
** Semicolons (';') are the only valid
** separator within compounds (newlines
** aren't legal separators within them)
*/
static bool is_separator(const parser_t *parser)
{
    return
        parser->current->type == TT_SEPARATOR &&
        *parser->current->start == ';';
}

/*
** Pretty self explanatory.
** Skips all separator tokens (if any).
*/
static void skip_separators(parser_t *parser)
{
    while (is_separator(parser))
        parser_next(parser);
}

/*
** Parses the body of a command compound.
** Note: at least one statement is required
** within the compound's body.
*/
static ast_node_buffer_t *parse_compound_body(parser_t *parser)
{
    ast_node_buffer_t *buffer = ast_node_buffer_create();
    ast_t *current_stmt = parse_statement(parser);

    ast_node_buffer_append(buffer, current_stmt);
    while (is_separator(parser)) {
        skip_separators(parser);
        if (parser->current->type == TT_RPAREN)
            break;
        current_stmt = parse_statement(parser);
        ast_node_buffer_append(buffer, current_stmt);
        if (current_stmt->type == AT_ERROR)
            return buffer;
    }
    return buffer;
}

/*
** Parses a parenthesis.
** Returns an AT_ERROR node on error
** (notably when the parenthesis is unmatched).
*/
ast_t *parse_parenthesis(parser_t *parser)
{
    ast_t *result = ast_create(AT_COMPOUND);

    parser_next(parser);
    result->data = parse_compound_body(parser);
    if (parser->current->type != TT_RPAREN) {
        parser_errno_set(PE_UNMATCHED_PARENTHESIS);
        return result;
    }
    parser_next(parser);
    return result;
}
