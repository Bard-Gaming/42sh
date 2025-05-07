/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_while_loop
*/

#include <42sh/shell.h>


/*
** Interprets a while loop.
**
** This will repeat the interpretation of the
** loop's body until the condition is false,
** which may never be the case.
*/
void shell_interpret_while_loop(ast_t *ast, sh_data_t *data)
{
    ast_while_stmnt_t *stmnt = ast->data;

    while (shell_interpret_condition(&stmnt->condition, data))
        shell_interpret(stmnt->body, data);
}
