/*
** EPITECH PROJECT, 2025
** Project - Minishell 1
** File description:
** Program entry
*/

#include <mysh/shell.h>


int main(int argc, char *argv[], char *env[])
{
    (void)argc;
    (void)argv;
    return shell_mainloop(env);
}
