/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_foreach_loop
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <stdlib.h>


static char *interpret_variable_name(ast_foreach_loop_t *loop, sh_data_t *data)
{
    sh_vector_t name_args = { 0 };
    char *result;

    shell_interpret_value(loop->variable, data, &name_args);
    if (name_args.count > 1) {
        fputs("foreach: Variable name must be a single argument.\n", stderr);
        sh_vector_delete(&name_args, NULL);
        return NULL;
    }
    result = name_args.data[0];
    name_args.data[0] = NULL;
    sh_vector_delete(&name_args, NULL);
    if (!sh_strisname(result, "foreach")) {
        free(result);
        return NULL;
    }
    return result;
}

/*
** Takes one parsed argument, iterating over
** all of its effective / expanded arguments
** by interpreting the body with the variable
** set to each of the arguments.
*/
static void iterate_argument(const char *var,
    ast_t *arg, ast_t *body, sh_data_t *data)
{
    sh_vector_t arguments = { 0 };

    shell_interpret_value(arg, data, &arguments);
    for (size_t i = 0; i < arguments.count; i++) {
        sh_data_setvar(data, var, arguments.data[i]);
        shell_interpret(body, data);
    }
    sh_vector_delete(&arguments, NULL);
}

/*
** Interprets a foreach loop.
**
** This runs a fixed number of iterations,
** updating a given variable
*/
void shell_interpret_foreach_loop(ast_t *ast, sh_data_t *data)
{
    ast_foreach_loop_t *loop = ast->data;
    char *variable_name = interpret_variable_name(loop, data);

    if (variable_name == NULL) {
        data->exit_status = 1;
        return;
    }
    for (size_t i = 0; i < loop->list->count; i++) {
        iterate_argument(
            variable_name, loop->list->nodes[i],
            loop->body, data
        );
    }
    free(variable_name);
}
