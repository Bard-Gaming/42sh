/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <mysh/types.h>
#include <42parser/ast.h>


static const sh_interpret_fnc_t visit_functions[AT_COUNT] = {
    [AT_COMMAND] = shell_interpret_command,
    [AT_OPERATION_AND] = shell_interpret_operation_and,
    [AT_OPERATION_OR] = shell_interpret_operation_or,
    [AT_PIPELINE] = shell_interpret_operation_pipe,
    [AT_PROGRAM] = shell_interpret_program,
};


/*
** Interpret an AST node, regardless of which
** type of node it is. Does nothing if the node's
** type is invalid.
**
** When a node needs interpretation, this is always
** the function that should be called, as the specific
** interpretation functions do not check whether or
** not the given node is of the valid type or not,
** making segfaults likely.
** This function handles this, meaning that no mistakes
** are possible.
*/
void shell_interpret(ast_t *ast, sh_data_t *data)
{
    sh_interpret_fnc_t visit = visit_functions[ast->type];

    if (visit == NULL)
        return;
    visit(ast, data);
}
