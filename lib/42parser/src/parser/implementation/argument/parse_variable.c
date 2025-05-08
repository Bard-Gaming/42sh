/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** parse_variable
*/

#include <42parser/parser.h>
#include <string.h>


static void skip_opening_bracket(const char **current, bool *is_bracket)
{
    if (**current != '{')
        return;
    *is_bracket = true;
    (*current)++;
}

static bool skip_closing_bracket(const char **current, const char *start)
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

static ast_t *create_var(const char *start, const char *end)
{
    ast_t *node = ast_create(AT_VARIABLE);

    node->data = strndup(start, end - start);
    if (node->data == NULL)
        node->type = AT_ERROR;
    return node;
}

static ast_t *parse_special_variable_generic(char var,
    const char **current, const char *end)
{
    size_t remaining = end - *current;
    char bracket_var[3] = { '{', var, '}' };
    ast_t *node;

    if (remaining >= 1 && **current == var) {
        node = create_var(*current, *current + 1);
        (*current)++;
        return node;
    }
    if (remaining >= 3 && strncmp(*current, bracket_var, 3) == 0) {
        node = create_var(*current + 1, *current + 2);
        *current += 3;
        return node;
    }
    return NULL;
}

/*
** Returns the parsed special variable node if
** successful, else returns NULL.
*/
static ast_t *parse_special_variable(const char **current, const char *end)
{
    ast_t *node = parse_special_variable_generic('?', current, end);

    if (node != NULL)
        return node;
    node = parse_special_variable_generic('#', current, end);
    if (node != NULL)
        return node;
    return parse_special_variable_generic('*', current, end);
}

/*
** Parses a variable within an argument.
** Note: Unlike the other argument parsing
** functions, this function can return NULL.
*/
ast_t *parse_variable(const char **current, const char *end)
{
    bool is_bracket = false;
    const char *start;
    ast_t *node;

    (*current)++;
    node = parse_special_variable(current, end);
    if (node != NULL)
        return node;
    if (**current != '{' && !lexer_is_variable_char(**current))
        return NULL;
    skip_opening_bracket(current, &is_bracket);
    start = *current;
    while (*current < end && lexer_is_variable_char(**current))
        (*current)++;
    if (is_bracket && !skip_closing_bracket(current, start))
        return ast_create(AT_ERROR);
    node = create_var(start, *current);
    if (is_bracket)
        (*current)++;
    return node;
}
