/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_command_append
*/

#include <42parser/ast.h>
#include <stdlib.h>


static void grow_command(ast_command_t *command)
{
    size_t new_capacity = command->arg_capacity > 0 ?
        command->arg_capacity * 2 : 4;
    char **new_buffer = malloc(new_capacity * sizeof(char *));

    if (new_buffer == NULL)
        return;
    for (size_t i = 0; i < command->arg_count; i++)
        new_buffer[i] = command->args[i];
    free(command->args);
    command->args = new_buffer;
    command->arg_capacity = new_capacity;
}

/*
** Append a token to a command data component.
** Does nothing on error.
*/
void ast_command_append(ast_command_t *command, const token_t *token)
{
    if (command->arg_count + 1 >= command->arg_capacity)
        grow_command(command);
    command->args[command->arg_count] = token_value(token);
    command->arg_count++;
    command->args[command->arg_count] = NULL;
}
