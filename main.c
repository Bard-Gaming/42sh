/*
** EPITECH PROJECT, 2025
** Project - Minishell 1
** File description:
** Program entry
*/

#include <mysh/shell.h>
#include <mysh/data.h>


int main(int argc, char *argv[], char *envp[])
{
    int exit_status;
    sh_data_t *shell_data = shell_init(envp);

    (void)argc;
    (void)argv;
    exit_status = shell_mainloop(shell_data);
    sh_data_delete(shell_data);
    return exit_status;
}
