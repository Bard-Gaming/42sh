/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_condition
*/

#include <42parser/parser.h>
#include <42parser/error.h>


/*
** Tells whether or not the current token
** matches the given char
*/
static bool is_char_token(const parser_t *parser, char c)
{
    return
        parser->current->type == TT_ARGUMENT &&
        parser->current->length == 1 &&
        *parser->current->start == c;
}

/*
** Parses a command condition.
** Command conditions are built as follows:
** "({" <expression> "})"
*/
static ast_condition_t parse_command_condition(parser_t *parser)
{
    ast_condition_t result = {
        .is_command = true
    };

    parser_next(parser);
    parser->stop_brace = true;
    result.condition.command = parse_expression(parser);
    parser->stop_brace = false;
    if (!is_char_token(parser, '}')) {
        parser_errno_set(PE_UNMATCHED_LBRACE);
        return result;
    }
    parser_next(parser);
    if (!parser_scan(parser, TT_RPAREN))
        parser_errno_set(PE_UNMATCHED_LPAREN);
    return result;
}

/*
** Parses a test condition.
** Test conditions are built as follows:
** "(" <arg>+ ")"
*/
static ast_condition_t parse_test_condition(parser_t *parser)
{
    ast_condition_t result = {
        .is_command = false,
        .condition.test_args = ast_node_buffer_create(),
    };
    ast_t *current;

    while (IS_ARGUMENT(parser->current->type)) {
        current = parse_subatom(parser);
        ast_node_buffer_append(result.condition.test_args, current);
        if (current->type == AT_ERROR)
            return result;
    }
    if (!parser_scan(parser, TT_RPAREN))
        parser_errno_set(PE_UNMATCHED_LPAREN);
    return result;
}

/*
** Error to use when a syntax error
** occurred.
*/
static ast_condition_t syntax_error(parser_errno_t error)
{
    parser_errno_set(error);
    return (ast_condition_t){ 0 };
}

/*
** Parses any kind of condition.
** Conditions can be either test conditions,
** or command conditions. More info on them
** is above this function.
** Sets P_ERRNO on error.
*/
ast_condition_t parse_condition(parser_t *parser)
{
    if (!parser_scan(parser, TT_LPAREN))
        return syntax_error(PE_UNMATCHED_RPAREN);
    if (is_char_token(parser, '{'))
        return parse_command_condition(parser);
    return parse_test_condition(parser);
}
