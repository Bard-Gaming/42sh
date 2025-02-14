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
    #include <sys/types.h>
    #include <stdio.h>


sh_data_t *shell_init(char *env[]);
int shell_mainloop(sh_data_t *data);
int shell_execline(char **line_buffer, sh_data_t *data);
pid_t shell_subprocess(const char *program, char **args, char **env);
char *shell_parse_command(const char *command, sh_env_t *env);
ssize_t shell_query_command(char **restrict lineptr, size_t *restrict n);


#endif
