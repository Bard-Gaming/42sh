/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_compound
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>


/*
** Displays an error message and
** returns the appropriate error
** value for when a fork fails.
*/
static void *fork_error(void)
{
    sh_puterr("Critical fork failure.\n");
    return NULL;
}

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
    pid_t subproc = fork();

    if (subproc < 0)
        return fork_error();
    if (subproc != 0) {
        waitpid(subproc, NULL, 0);
        return NULL;
    }
    for (size_t i = 0; i < compound->count; i++)
        shell_interpret(compound->nodes[i], data);
    _exit(data->exit_status);
}
