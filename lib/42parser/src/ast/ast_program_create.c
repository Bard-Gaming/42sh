/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_program_create
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Create a new program node.
*/
ast_program_t *ast_program_create(void)
{
    ast_program_t *program = malloc(sizeof(ast_program_t));

    program->nodes = NULL;
    program->count = 0;
    program->capacity = 0;
    return program;
}
