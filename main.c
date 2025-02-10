/*
** EPITECH PROJECT, 2025
** Project - Minishell 1
** File description:
** Program entry
*/

#include <mysh/arguments.h>


int main(void)
{
    argument_buffer_t *buffer = argument_buffer_create();

    argument_buffer_append(buffer, "bob");
    argument_buffer_append(buffer, "hello");
    argument_buffer_delete(buffer);
    return 0;
}
