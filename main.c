/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Program entry
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <readline.h>
#include <unistd.h>

void file_as_argument(sh_data_t *data, int argc, char *argv[])
{
    int fd = open(argv[1]);
    char *command = NULL;

    if (fd < 0)
        return;
    for (int i = 1; i < argc; i++) {
        sh_data_setvar(data, , argv[i]);
    }
    command = readline(fd);
    close(fd);
    shell_system(command, data);
    readline_free();
}

int main(int argc, char *argv[], char *envp[])
{
    sh_data_t *shell_data = sh_data_from_unix_env(envp);
    unsigned char status;


    if (argc > 1)
        file_as_argument(shell_data, argc, argv);
    else
        shell_mainloop(shell_data);
    status = shell_data->exit_status;
    sh_data_delete(shell_data);
    return status;
}
