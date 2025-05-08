/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_input_dynamic
*/

#include <42parser/parser.h>
#include <42parser/preparser.h>
#include <string.h>
#include <stdlib.h>


static ast_t *dynamically_parse(parser_t *parser, char **input)
{
    ast_t *result;

    while (parser->current->type == TT_SEPARATOR)
        parser_next(parser);
    if (parser->current->type == TT_EOF) {
        free(*input);
        *input = NULL;
        return NULL;
    }
    result = parse_statement(parser);
    free(*input);
    *input = strdup(parser->lexer.start);
    return result;
}

/*
** Dynamically parses the given input.
** This means that only a single statement is
** parsed per call to this function.
** To get the next statement for the same input,
** simply pass NULL as input argument (assuming
** a call to this function with valid input
** has already happened).
*/
ast_t *parse_input_dynamic(char **input)
{
    char *expanded_input;
    parser_t parser;
    ast_t *result;

    parser_errno_set(PE_NONE);
    expanded_input = preparse(*input);
    if (expanded_input == NULL)
        return NULL;
    parser_init(&parser, expanded_input);
    result = dynamically_parse(&parser, input);
    parser_term(&parser);
    free(expanded_input);
    if (P_ERRNO == PE_NONE)
        return result;
    ast_delete(result);
    free(*input);
    *input = NULL;
    return NULL;
}
