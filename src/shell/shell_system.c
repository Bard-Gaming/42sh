/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_system
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42parser/parser.h>
#include <42parser/error.h>


/*
** Make the shell run a given command.
** If the given command is empty, this
** does nothing.
** Note, however, that the given command
** should not be NULL.
*/
void shell_system(const char *command, sh_data_t *data)
{
    ast_t *parsed_command = parse_input(command);

    if (parsed_command != NULL)
        shell_interpret(parsed_command, data);
    if (P_ERRNO != 0) {
        parser_perror(NULL);
        data->exit_status = 1;
    }
    ast_delete(parsed_command);
}
