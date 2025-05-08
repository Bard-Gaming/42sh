/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_if_statement
*/

#include <42parser/parser.h>
#include <42parser/error.h>
#include <42parser/ast.h>


/*
** Tells whether or not the parser's current
** token is a body's end token or not.
*/
static bool is_body_end(const parser_t *parser)
{
    return
        token_match(parser->current, "endif") ||
        token_match(parser->current, "else") ||
        parser->current->type == TT_ERROR ||
        parser->current->type == TT_EOF;
}

/*
** Parses an if condition's body.
** This body is similar to a program node,
** with the exception that it is bounded by
** the endif statement.
*/
static ast_t *parse_body(parser_t *parser)
{
    ast_t *node = ast_create(AT_PROGRAM);
    ast_node_buffer_t *prog = ast_node_buffer_create();
    ast_t *current_stmt;

    node->data = prog;
    do {
        while (parser->current->type == TT_SEPARATOR)
            parser_next(parser);
        if (is_body_end(parser))
            break;
        current_stmt = parse_statement(parser);
        ast_node_buffer_append(prog, current_stmt);
        if (current_stmt->type == AT_ERROR)
            return node;
    } while (parser->current->type == TT_SEPARATOR);
    return node;
}

/*
** Parses an if substatement.
** If statements are simply the
**
** "if" <cond> "then"
**     <body>
**
** part of if statements.
*/
static void parse_substatement(parser_t *parser, ast_if_stmnt_t *data)
{
    ast_condition_t condition;
    ast_t *body = NULL;

    condition = parse_condition(parser);
    if (P_ERRNO == PE_UNMATCHED_RPAREN)
        return parser_errno_set(PE_IF_EXPRESSION_SYNTAX);
    if (P_ERRNO == PE_UNMATCHED_LBRACE)
        parser_errno_set(PE_IF_MISSING_BRACE);
    if (!parser_scan_keyword(parser, "then"))
        parser_errno_set_weak(PE_MISSING_THEN_ENDIF);
    if (P_ERRNO == PE_NONE)
        body = parse_body(parser);
    ast_if_stmnt_add(data, condition, body);
    if (token_match(parser->next, "if"))
        parser_scan_keyword(parser, "else");
}

/*
** Parses an if statement.
** If statements are built as follows:
**
** -----------------------------------
** "if" "(" <args> ")" "then"
**     <body>
** "endif"
** -----------------------------------
** "if" <expr> <sep> "then"
**     <body>
** "endif"
** -----------------------------------
**
** Note: indentation is optional.
*/
ast_t *parse_if_statement(parser_t *parser)
{
    ast_t *node = ast_create(AT_IF_STATEMENT);
    ast_if_stmnt_t *data = ast_if_stmnt_create();

    node->data = data;
    while (parser_scan_keyword(parser, "if"))
        parse_substatement(parser, data);
    if (parser_scan_keyword(parser, "else"))
        data->bodies[data->count] = parse_body(parser);
    if (!parser_scan_keyword(parser, "endif"))
        parser_errno_set_weak(PE_MISSING_THEN_ENDIF);
    return node;
}
