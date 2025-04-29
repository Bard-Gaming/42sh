/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_value
*/

#include <42sh/shell.h>


static const sh_interpret_val_fnc_t visit_functions[AT_COUNT] = {
    [AT_VARIABLE] = shell_interpret_variable,
    [AT_REDIRECT] = shell_interpret_redirect,
    [AT_ARGUMENT] = shell_interpret_argument,
    [AT_ARGUMENT_STR] = shell_interpret_argument,
    [AT_SUBSTITUTION] = shell_interpret_substitution,
    [AT_RAW_ARGUMENT] = shell_interpret_raw_argument,
};

/*
** Interprets a value node and
** returns the resulting string.
*/
char *shell_interpret_value(ast_t *ast, sh_data_t *data)
{
    sh_interpret_val_fnc_t visit = visit_functions[ast->type];

    if (visit == NULL)
        return NULL;
    return visit(ast, data);
}
