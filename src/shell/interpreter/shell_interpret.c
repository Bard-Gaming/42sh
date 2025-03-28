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


static sh_interpret_fnc_t get_interpret_fnc(const ast_t *node)
{
    static sh_interpret_fnc_t function_list[AT_COUNT] = {
        [AT_COMMAND] = shell_interpret_command,
        [AT_OPERATION_AND] = shell_interpret_operation_and,
        [AT_OPERATION_OR] = shell_interpret_operation_or,
        [AT_PIPELINE] = shell_interpret_operation_pipe,
        [AT_PROGRAM] = shell_interpret_program,
    };

    return function_list[node->type];
}

/*
** Visit the appropriate function
** to interpret the given node.
*/
void shell_interpret(ast_t *ast, sh_data_t *data)
{
    sh_interpret_fnc_t visit = get_interpret_fnc(ast);

    if (visit == NULL)
        return;
    visit(ast, data);
}
