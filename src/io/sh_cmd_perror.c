/*
** EPITECH PROJECT, 2025
** Project - 42sh
** File description:
** Implementation for
** sh_cmd_perror
*/

#include <mysh/io.h>
#include <errno.h>
#include <string.h>


/*
** Works the same as the standard
** sh_perror function, with the
** exception that it has some
** custom messages that are related
** to command execution.
*/
void sh_cmd_perror(const char *restrict prefix)
{
    sh_puterr(prefix);
    sh_puterr(": ");
    if (errno == ENOENT)
        return sh_puterr("Command not found.\n");
    sh_puterr(strerror(errno));
    if (errno == ENOEXEC)
        sh_puterr(". Binary file not executable");
    sh_puterr(".\n");
}
