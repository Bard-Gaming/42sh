/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_compound
*/

#include <42sh/shell.h>


/*
** Interprets a command compound.
** Command compounds are different from normal
** chained commands in that they are run inside of
** a subprocess / fork, meaning that all changes
** made to the shell don't affect the main process.
*/
void *shell_interpret_compound(ast_t *ast, sh_data_t *data)
{
    ast_node_buffer_t *compound = ast->data;

    for (size_t i = 0; i < compound->count; i++)
        shell_interpret(compound->nodes[i], data);
    return NULL;
}
