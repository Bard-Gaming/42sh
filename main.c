/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Program entry
*/

#include <42sh/shell.h>
#include <42sh/data.h>
#include <42sh/io.h>
#include <readline.h>


static void run_file(sh_data_t *data, char *argv[])
{
    int status = shell_run_file(data, argv[1], argv + 1);

    if (status < 0) {
        sh_perror(argv[1]);
        data->exit_status = 1;
    }
}

int main(int argc, char *argv[], char *envp[])
{
    sh_data_t *shell_data = sh_data_from_unix_env(envp);
    unsigned char status;

    if (argc > 1)
        run_file(shell_data, argv);
    else
        shell_mainloop(shell_data);
    status = shell_data->exit_status;
    sh_data_delete(shell_data);
    readline_free();
    return status;
}
