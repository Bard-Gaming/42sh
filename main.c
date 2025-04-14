/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Program entry
*/

#include <42sh/string.h>
#include <42sh/shell.h>
#include <42sh/data.h>
#include <readline.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>


void file_as_argument(sh_data_t *data, char *filename, char *argv[])
{
    int fd = open(filename, O_RDONLY);
    char *command = NULL;
    char arg_name[ITOA_MAX];

    if (fd < 0)
        return;
    for (int i = 0; argv[i]; i++) {
        sh_itoa(arg_name, i);
        sh_data_setvar(data, arg_name, argv[i]);
    }
    command = readline(fd);
    close(fd);
    shell_system(command, data);
    readline_free();
}

void parse_42shrc(sh_data_t *data)
{
    char *home = strdup(sh_data_getvar(data, "HOME"));
    char *path_rc = sh_strjoin(home, "/.42shrc");
    void **argv = malloc(sizeof(char *));
    argv[0] = NULL;

    file_as_argument(data, path_rc, argv);
    free(home);
    free(path_rc);
}

int main(int argc, char *argv[], char *envp[])
{
    sh_data_t *shell_data = sh_data_from_unix_env(envp);
    unsigned char status;

    parse_42shrc(shell_data);
    if (argc > 1)
        file_as_argument(shell_data, argv[1], argv + 1);
    else
        shell_mainloop(shell_data);
    status = shell_data->exit_status;
    sh_data_delete(shell_data);
    return status;
}
