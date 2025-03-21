/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_program
*/

#include <mysh/shell.h>
#include <mysh/data.h>
#include <42parser/ast.h>


/*
** Interpret a whole program.
** A program is a collection of
** statements, so interpreting
** it effectively means interpreting
** all of its elements/children.
*/
void shell_interpret_program(ast_t *ast, sh_data_t *data)
{
    ast_program_t *program = ast->data;

    for (size_t i = 0; i < program->count; i++)
        shell_interpret(program->nodes[i], data);
}
