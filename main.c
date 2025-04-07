/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Program entry
*/

#include <42sh/shell.h>
#include <42sh/data.h>


int main(int argc, char *argv[], char *envp[])
{
    sh_data_t *shell_data = sh_data_from_unix_env(envp);
    unsigned char status;

    (void)argc;
    (void)argv;
    shell_mainloop(shell_data);
    status = shell_data->exit_status;
    sh_data_delete(shell_data);
    return status;
}
