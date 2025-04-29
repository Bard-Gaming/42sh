/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_substitution
*/

#include <42sh/shell.h>
#include <42sh/string.h>
#include <42sh/vector.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <42parser/ast.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>


/*
** Displays the message that should be
** displayed when a pipe fails.
*/
static char *pipe_error(void)
{
    sh_puterr("Broken pipe.\n");
    return NULL;
}

/*
** Displays the message that should be
** displayed when a pipe fails.
*/
static char *fork_error(void)
{
    sh_puterr("Critical fork failure.\n");
    return NULL;
}

/*
** Cleans up the resulting output string.
*/
static void clean_result(char *result)
{
    size_t len = strlen(result);

    if (result[len - 1] == '\n')
        result[len - 1] = '\0';
}

/*
** Reads from the read-end of the given pipe
** and fills a char buffer to fit the output.
*/
static char *string_value(int *pipefd, pid_t subproc)
{
    sh_vector_t result_aggr = { 0 };
    ssize_t read_len;
    char buffer[128];
    char *result;

    close(pipefd[1]);
    do {
        memset(buffer, '\0', 128 * sizeof(char));
        read_len = read(pipefd[0], buffer, 127);
        sh_vector_push_back(&result_aggr, sh_strdup(buffer));
    } while (read_len > 0);
    close(pipefd[0]);
    waitpid(subproc, NULL, 0);
    result = sh_strjoinvec((const char **)result_aggr.data);
    clean_result(result);
    sh_vector_delete(&result_aggr, NULL);
    return result;
}

/*
** Interprets a command substitution.
**
** This works by executing the AST in a child
** process, and storing the output into a string
** buffer.
*/
char *shell_interpret_substitution(ast_t *ast, sh_data_t *data)
{
    int pipefd[2];
    pid_t subproc;

    if (pipe(pipefd) != 0)
        return pipe_error();
    subproc = fork();
    if (subproc < 0)
        return fork_error();
    if (subproc != 0)
        return string_value(pipefd, subproc);
    close(pipefd[0]);
    data->write_file = pipefd[1];
    shell_interpret(ast->data, data);
    close(pipefd[1]);
    exit(data->exit_status);
}
