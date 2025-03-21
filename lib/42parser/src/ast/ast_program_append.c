/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_program_append
*/

#include <42parser/ast.h>
#include <stdlib.h>


static void grow_program(ast_program_t *program)
{
    size_t new_capacity = program->capacity == 0 ?
        AST_PROG_INIT_CAP : program->capacity * 2;
    ast_t **new_data = malloc(new_capacity * sizeof(ast_t *));

    for (size_t i = 0; i < program->count; i++)
        new_data[i] = program->nodes[i];
    free(program->nodes);
    program->nodes = new_data;
    program->capacity = new_capacity;
}

/*
** Append a node to the given
** program node.
*/
void ast_program_append(ast_program_t *program, ast_t *node)
{
    if (program->count == program->capacity)
        grow_program(program);
    program->nodes[program->count] = node;
    program->count++;
}
