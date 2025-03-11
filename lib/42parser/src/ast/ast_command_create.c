/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_command_create
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Create a command data component.
** Returns NULL on error.
*/
ast_command_t *ast_command_create(void)
{
    ast_command_t *command = malloc(sizeof(ast_command_t));

    if (command == NULL)
        return NULL;
    command->args = NULL;
    command->arg_count = 0;
    command->arg_capacity = 0;
    return command;
}
