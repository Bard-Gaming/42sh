/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Header file for all things
** related to the shell
*/

#ifndef MYSH_SHELL_H
    #define MYSH_SHELL_H
    #include <sys/types.h>
    #include <stdio.h>


int shell_mainloop(char *env[]);
void shell_execline(char **line_buffer, char *env[]);
pid_t shell_subprocess(const char *program, char **args, char *env[]);
char *shell_parse_command(const char *command, char *env[]);
ssize_t shell_query_command(char **restrict lineptr,
    size_t *restrict n, FILE *restrict stream);


#endif
