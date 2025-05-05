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


/*
** Runs the test command with the
** parsed arguments. This allows
** for conditions such as:
** ( a == b )
** ( 3 -gt 2 )
** etc...
**
*/
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

/*
** Tells whether the given condition is
** evaluated to true or not.
*/
static bool condition_is_true(ast_condition_t *condition, sh_data_t *data)
{
    if (!condition->is_command)
        return test_condition(condition->condition.test_args, data);
    shell_interpret(condition->condition.command, data);
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
    ast_if_stmnt_t *stmnt = ast->data;

    for (size_t i = 0; i < stmnt->count; i++) {
        if (!condition_is_true(stmnt->conditions + i, data))
            continue;
        shell_interpret(stmnt->bodies[i], data);
        return;
    }
    if (stmnt->bodies[stmnt->count] != NULL)
        shell_interpret(stmnt->bodies[stmnt->count], data);
}
