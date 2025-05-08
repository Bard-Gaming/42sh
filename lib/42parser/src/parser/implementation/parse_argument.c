/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_argument
*/

#include <42parser/parser.h>
#include <42parser/ast.h>
#include <42parser/token.h>
#include <string.h>
#include <stdlib.h>


static void parse_substitution(ast_argument_t *arg,
    const char **current, const char *end)
{
    const char *start = *current + 1;
    char *input;
    ast_t *node;

    (*current)++;
    while (*current < end && **current != '`')
        (*current)++;
    if (*current == end)
        return parser_errno_set(PE_UNMATCHED_BACKTICK);
    node = ast_create(AT_SUBSTITUTION);
    input = strndup(start, *current - start);
    (*current)++;
    node->data = parse_input(input);
    free(input);
    if (node->data != NULL)
        ast_argument_add_node(arg, node);
    else
        free(node);
}

static void handle_bracket_start(const char **current, bool *is_bracket)
{
    *is_bracket = true;
    (*current)++;
}

static bool handle_bracket_end(const char **current, const char *start)
{
    if (**current != '}') {
        parser_errno_set(PE_UNMATCHED_LBRACE);
        return false;
    }
    if (*current - start == 0) {
        parser_errno_set(PE_ILLEGAL_VAR_NAME);
        return false;
    }
    return true;
}

static void add_var(ast_argument_t *arg, const char *start, const char *end)
{
    ast_t *node = ast_create(AT_VARIABLE);

    ast_argument_add_node(arg, node);
    node->data = strndup(start, end - start);
}

static bool parse_special_variable(char var, ast_argument_t *arg,
    const char **current, const char *end)
{
    size_t remaining = end - *current;
    char bracket_var[3] = { '{', var, '}' };

    if (remaining >= 1 && **current == var) {
        add_var(arg, *current, *current + 1);
        (*current)++;
        return true;
    }
    if (remaining >= 3 && strncmp(*current, bracket_var, 3) == 0) {
        add_var(arg, *current + 1, *current + 2);
        *current += 3;
        return true;
    }
    return false;
}

static bool has_parsed_special_variable(ast_argument_t *arg,
    const char **current, const char *end)
{
    return
        parse_special_variable('?', arg, current, end) ||
        parse_special_variable('#', arg, current, end) ||
        parse_special_variable('*', arg, current, end);
}

static void parse_variable(ast_argument_t *arg,
    const char **current, const char *end)
{
    const char *start;
    bool is_bracket = false;

    (*current)++;
    if (has_parsed_special_variable(arg, current, end))
        return;
    if (**current != '{' && !lexer_is_variable_char(**current))
        return ast_argument_add_char(arg, '$');
    if (**current == '{')
        handle_bracket_start(current, &is_bracket);
    start = *current;
    while (*current < end && lexer_is_variable_char(**current))
        (*current)++;
    if (is_bracket && !handle_bracket_end(current, start))
        return;
    add_var(arg, start, *current);
    if (is_bracket)
        (*current)++;
}

static void parse_raw_string(ast_argument_t *arg,
    const char **current, const char *end)
{
    ast_t *node = ast_create(AT_RAW_ARGUMENT);
    const char *start = *current + 1;

    (*current)++;
    while (**current != '\'' && *current < end)
        (*current)++;
    (*current)++;
    node->data = strndup(start, *current - start - 1);
    ast_argument_add_node(arg, node);
}

static void parse_arg_char(ast_argument_t *arg,
    const char **current, const char *end)
{
    if (**current == '$')
        return parse_variable(arg, current, end);
    if (**current == '`')
        return parse_substitution(arg, current, end);
    if (**current == '\'')
        return parse_raw_string(arg, current, end);
    ast_argument_add_char(arg, **current);
    (*current)++;
}

/*
** Parses an argument, which includes
** parsing variables.
*/
ast_t *parse_argument(parser_t *parser)
{
    ast_t *node = ast_create(AST_ARG_TYPE(parser->current->type));
    const char *end = parser->current->start + parser->current->length;
    const char *current = parser->current->start;

    parser_next(parser);
    node->data = ast_argument_create();
    while (current < end)
        parse_arg_char(node->data, &current, end);
    return node;
}
