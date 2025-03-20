/*
** EPITECH PROJECT, 2025
** Project - 42parser
** File description:
** Implementation for
** ast_command_create
*/

#include <42parser/ast.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>


/*
** Initializes the io files of a command
** to their default values. The default
** values are the file descriptors:
** - 0 for stdin,
** - 1 for stdout,
** - 2 for stderr.
*/
static void set_default_io_files(ast_command_t *command)
{
    for (intptr_t i = 0; i < 3; i++) {
        command->is_path[i] = false;
        command->io_files[i] = (void *)i;
        command->open_flags[i] = i == 0 ?
            O_RDONLY : O_CREAT | O_WRONLY | O_TRUNC;
    }
}

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
    set_default_io_files(command);
    return command;
}
