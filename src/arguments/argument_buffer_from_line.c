/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** argument_buffer_from_line
*/

#include <mysh/arguments.h>
#include <stdlib.h>


/*
** Create an argument buffer from a
** line of arguments
*/
argument_buffer_t *argument_buffer_from_line(const char *line)
{
    argument_buffer_t *buf = argument_buffer_create();
    char *current_arg = arguments_parse_arg(&line);

    while (current_arg != NULL) {
        argument_buffer_append(buf, current_arg);
        free(current_arg);
        current_arg = arguments_parse_arg(&line);
    }
    return buf;
}
