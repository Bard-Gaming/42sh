/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_program_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Delete a program node and
** all of its containing data.
*/
void ast_program_delete(ast_program_t *program)
{
    for (size_t i = 0; i < program->count; i++)
        ast_delete(program->nodes[i]);
    free(program->nodes);
    free(program);
}
