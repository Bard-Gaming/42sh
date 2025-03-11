/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all things
** related to the shell
*/

#ifndef MYSH_SHELL_H
    #define MYSH_SHELL_H
    #define _GNU_SOURCE
    #include <mysh/env.h>
    #include <42parser/ast.h>
    #include <sys/types.h>
    #include <stdio.h>


void shell_mainloop(sh_data_t *data);
int shell_exec_command(char **args, sh_data_t *data);
void shell_interpret_input(ast_t *ast, sh_data_t *data);
pid_t shell_subprocess(const char *program, char **args, char **env);
char *shell_get_command_abs_path(const char *command, sh_env_t *env);
char *shell_query_input(void);


#endif
