/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_value
*/

#include <42sh/shell.h>


static const sh_interpret_val_fnc_t visit_functions[AT_COUNT] = {
    [AT_REDIRECT] = shell_interpret_redirect,
    [AT_ARGUMENT] = shell_interpret_argument,
    [AT_RAW_ARGUMENT] = shell_interpret_raw_argument,
};

/*
** Interprets a value node.
**
** The extra parameter specifies the options
** that should be applied when interpreting
** the given node.
**
** These options are:
** - SH_INTRPT_SPLIT (whether or not to split an argument)
** - SH_INTRPT_VARS  (whether or not to parse args)
** - SH_INTRPT_GLOBS (whether or not to parse globs, implies vars)
**
** Options can be combined by OR'ing them together.
*/
void *shell_interpret_value(ast_t *ast, sh_data_t *data, int opts)
{
    sh_interpret_val_fnc_t visit = visit_functions[ast->type];

    if (visit == NULL)
        return NULL;
    return visit(ast, data, opts);
}
