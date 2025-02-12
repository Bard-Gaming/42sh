/*
** EPITECH PROJECT, 2025
** Project - Minishell 1
** File description:
** Program entry
*/

#include <mysh/shell.h>
#include <mysh/env.h>


int main(int argc, char *argv[], char *envp[])
{
    int exit_status;
    sh_env_t *shell_env = sh_env_from_unix((const char **)envp);

    (void)argc;
    (void)argv;
    exit_status = shell_mainloop(shell_env);
    sh_env_delete(shell_env);
    return exit_status;
}
