/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_endif
*/

#include <42sh/builtins.h>
#include <42sh/io.h>


/*
** Implementation for the shell's builtin
** endif command.
** This command does nothing, as the syntax for
** if statements is handled by the parser.
** Its existence is solely to allow the user
** to write endif outside of if statements
** (even if this doesn't really make sense).
*/
int builtin_endif(char *args[], UNUSED sh_data_t *data)
{
    if (args[1] != NULL) {
        sh_puterr("endif: Too many arguments.\n");
        return 1;
    }
    return 0;
}
