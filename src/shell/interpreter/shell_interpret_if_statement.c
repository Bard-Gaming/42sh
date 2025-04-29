/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_if_statement
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42parser/ast.h>


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

    shell_interpret(cond->condition, data);
    if (data->exit_status == 0)
        shell_interpret(cond->body, data);
}
