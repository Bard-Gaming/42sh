/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** shell_interpret_command
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/vector.h>
#include <unistd.h>
#include <stdlib.h>
#include <glob.h>

static size_t perform_globbing(char **argv, glob_t *globbuf)
{
    size_t i = 0;
    size_t total = 0;
    int flags = GLOB_NOCHECK | GLOB_TILDE;

    globbuf->gl_offs = 0;
    for (i = 0; argv[i] != NULL; i++) {
        if (total)
            flags |= GLOB_APPEND;
        if (glob(argv[i], flags, NULL, globbuf) != 0)
            continue;
        total = globbuf->gl_pathc;
    }
    return total;
}

static char **build_argv_from_glob(const glob_t *globbuf, size_t total)
{
    size_t j;
    char **new_argv = malloc(sizeof(char *) * (total + 1));

    if (!new_argv)
        return NULL;
    for (j = 0; j < total; j++)
        new_argv[j] = strdup(globbuf->gl_pathv[j]);
    new_argv[total] = NULL;
    return new_argv;
}

static char **apply_globbing(char **argv)
{
    glob_t globbuf;
    size_t total;
    char **new_argv = NULL;

    total = perform_globbing(argv, &globbuf);
    new_argv = build_argv_from_glob(&globbuf, total);
    globfree(&globbuf);
    return new_argv;
}

/*
** Sets up the necessary io redirections and
** argument vector, which are required to
** properly run the command.
*/
static bool setup(ast_node_buffer_t *cmd, sh_data_t *data, sh_vector_t *argv)
{
    char *current_arg;

    for (size_t i = 0; i < cmd->count; i++) {
        current_arg = shell_interpret_value(cmd->nodes[i], data);
        if (!data->success)
            return false;
        if (current_arg == NULL)
            continue;
        sh_vector_push_back(argv, current_arg);
    }
    return true;
}

/*
** Cleans up io redirections, as well
** as the given argument vector.
*/
static void cleanup(sh_data_t *data, sh_vector_t *argv)
{
    for (int file = 0; file < 3; file++) {
        if (data->should_close[file])
            close(data->io_files[file]);
        data->should_close[file] = false;
        data->io_files[file] = file;
    }
    sh_vector_delete(argv, NULL);
}

static void free_globbed_argv(char **globbed_argv)
{
    for (size_t i = 0; globbed_argv[i] != NULL; i++)
        free(globbed_argv[i]);
    free(globbed_argv);
}

/*
** Interpret a command.
** Applies the necessary IO redirections,
** interprets the all of the command's
** arguments, then executes the given command.
*/
void shell_interpret_command(ast_t *ast, sh_data_t *data)
{
    sh_vector_t argv = { 0 };
    bool success = false;
    char **globbed_argv = NULL;

    success = setup(ast->data, data, &argv);
    if (success == true) {
        globbed_argv = apply_globbing((char **)argv.data);
        if (globbed_argv != NULL) {
            data->exit_status = shell_exec_command(globbed_argv, data);
            liberer_globbed_argv(globbed_argv);
        } else {
            data->exit_status = 1;
        }
    } else {
        data->exit_status = 1;
    }
}
