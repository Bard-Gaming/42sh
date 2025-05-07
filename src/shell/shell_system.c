/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_system
*/

#include <42sh/shell.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42parser/parser.h>
#include <42parser/error.h>
#include <stdlib.h>


/*
** Make the shell run a given command.
** If the given command is empty, this
** does nothing.
** Note, however, that the given command
** may never be NULL.
**
** Note: The user has to call shell_init()
** prior to calling this function.
*/
void shell_system(const char *command, sh_data_t *data)
{
    char *input = sh_strdup(command);
    ast_t *parsed_command = parse_input_dynamic(&input);

    while (parsed_command != NULL) {
        shell_interpret(parsed_command, data);
        ast_delete(parsed_command);
        parsed_command = parse_input_dynamic(&input);
    }
    free(input);
    if (P_ERRNO != PE_NONE) {
        parser_perror(NULL);
        data->exit_status = 1;
    }
}
