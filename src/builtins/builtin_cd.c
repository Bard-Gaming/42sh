/*
** EPITECH PROJECT, 2024
** Project - Minishell 1
** File description:
** Implementation for
** builtin_cd
*/

#include <mysh/builtins.h>
#include <mysh/string.h>
#include <mysh/io.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>


static const char *get_home_dir(char *env[])
{
    while (*env != NULL) {
        if (sh_strncmp(*env, "HOME=", 5) == 0)
            return *env + 5;
        env++;
    }
    return "";
}

int builtin_cd(const char *args[], char *env[])
{
    struct stat stat_buf;
    const char *path;

    if (args[1] != NULL && args[2] != NULL) {
        sh_puterr("cd: Too many arguments.\n");
        return 84;
    }
    path = args[1] == NULL ? get_home_dir(env) : args[1];
    if (stat(path, &stat_buf) != 0) {
        sh_puterr(path);
        sh_puterr(": No such file or directory.\n");
        return 84;
    }
    chdir(path);
    return 0;
}
