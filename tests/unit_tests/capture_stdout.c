/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** capture_stdout
*/

#include "tests.h"
#include <42sh/data.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


char *capture_stdout(const char *command)
{
    FILE *fp = tmpfile();
    int stdout_fd;
    char *result;

    if (!fp)
        return NULL;
    stdout_fd = dup(fileno(stdout));
    fflush(stdout);
    dup2(fileno(fp), fileno(stdout));
    system(command);
    fflush(stdout);
    dup2(stdout_fd, fileno(stdout));
    close(stdout_fd);
    fseek(fp, 0, SEEK_SET);
    result = malloc(4096);
    fread(result, sizeof(char), 4095, fp);
    result[4095] = '\0';
    fclose(fp);
    return result;
}
