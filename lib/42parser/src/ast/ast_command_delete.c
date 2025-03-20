/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_command_delete
*/

#include <42parser/ast.h>
#include <stdlib.h>


/*
** Delete a command data component.
*/
void ast_command_delete(ast_command_t *command)
{
    for (int i = 0; i < 3; i++)
        if (command->is_path[i])
            free(command->io_files[i]);
    for (size_t i = 0; i < command->arg_count; i++)
        free(command->args[i]);
    free(command->args);
    free(command);
}
