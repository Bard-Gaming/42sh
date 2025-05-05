/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** builtin_reload
*/

#include <42sh/builtins.h>
#include <42sh/memory.h>
#include <42sh/string.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <readline.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


/*
** Reload doesn't support any
** arguments, so return this function
** when any are given.
*/
static int too_many_args_err(void)
{
    sh_puterr("reload: Too many arguments.\n");
    return 84;
}

/*
** Reloading in pipes would lead to some
** pretty weird behaviour. Whilst this
** wouldn't cause any bugs / inconsistencies,
** it would lead to odd behaviour, which would
** make the shell feel clankier, which goes
** against its design, hence this function.
*/
static int pipe_err(void)
{
    sh_puterr("reload: Reloading in pipes is not supported.\n");
    return 84;
}

/*
** Creates an argument buffer used when
** reloading the shell with the exec syscall.
*/
static char **get_reload_args(sh_data_t *data)
{
    char **args = shmalloc(2 * sizeof(char *));

    args[0] = sh_strdup(data->shell_path);
    args[1] = NULL;
    return args;
}

/*
** Implementation for the shell's builtin
** reload command.
** This command allows the user to hot reload
** the shell, preserving its environment.
*/
int builtin_reload(char *args[], sh_data_t *data)
{
    char **env;

    if (args[1] != NULL)
        return too_many_args_err();
    if (IS_PIPE(data))
        return pipe_err();
    ;
    args = get_reload_args(data);
    env = sh_env_create(data);
    sh_data_delete(data);
    readline_free();
    ;
    execve(args[0], args, env);
    ;
    sh_puterr("reload: Shell binary not found.\n");
    sh_env_delete(env);
    free(args[0]);
    free(args);
    exit(84);
}
