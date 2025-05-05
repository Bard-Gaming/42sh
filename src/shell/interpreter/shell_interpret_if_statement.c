/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_if_statement
*/

#include <42sh/shell.h>
#include <42sh/vector.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42parser/ast.h>


static bool test_condition(ast_node_buffer_t *args, sh_data_t *data)
{
    sh_vector_t argv = { 0 };
    int status;

    sh_vector_push_back(&argv, sh_strdup("test"));
    for (size_t i = 0; i < args->count; i++)
        shell_interpret_value(args->nodes[i], data, &argv);
    status = shell_exec_command((char **)argv.data, data);
    sh_vector_delete(&argv, NULL);
    return status == 0;
}

static bool condition_is_true(ast_conditional_t *cond, sh_data_t *data)
{
    if (!cond->is_command)
        return test_condition(cond->condition.test_args, data);
    shell_interpret(cond->condition.command, data);
    return data->exit_status == 0;
}

/*
** Interprets an if statement.
**
** Executes the conditional's body if the
** given expression is truthy (i.e. has an exit)
** status of 0.
*/
void shell_interpret_if_statement(ast_t *ast, sh_data_t *data)
{
    ast_conditional_t *cond = ast->data;

    if (condition_is_true(cond, data))
        shell_interpret(cond->body, data);
}
