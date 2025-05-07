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
    ast_if_stmnt_t *stmnt = ast->data;

    for (size_t i = 0; i < stmnt->count; i++) {
        if (!shell_interpret_condition(stmnt->conditions + i, data))
            continue;
        shell_interpret(stmnt->bodies[i], data);
        return;
    }
    if (stmnt->bodies[stmnt->count] != NULL)
        shell_interpret(stmnt->bodies[stmnt->count], data);
}
