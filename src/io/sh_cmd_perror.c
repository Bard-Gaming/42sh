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


static void print_custom_noexec(void)
{
    sh_puterr(". Binary file not executable");
}

static void print_custom_access(void)
{
    sh_puterr("Command not found.\n");
}

/*
** Works the same as the standard
** sh_perror function, with the
** exception that it has some
** custom messages that are related
** to command execution.
*/
void sh_cmd_perror(const char *prefix)
{
    sh_puterr(prefix);
    sh_puterr(": ");
    if (errno == ENOENT)
        return print_custom_access();
    sh_puterr(strerror(errno));
    if (errno == ENOEXEC)
        print_custom_noexec();
    sh_puterr(".\n");
}
